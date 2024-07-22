// Copyright (c) 2010-2016 Quadralay Corporation.  All rights reserved.
//
// ePublisher 2016.1
//
// Validated with JSLint <http://www.jslint.com/>
//

window.onload = function() {
    var storage = window.localStorage['search'];
    if (storage !== undefined) {
        var info = JSON.parse(storage);
        delete window.localStorage['search'];
        if (info.action === 'search_display_link') {
            Search.SearchQueryHighlight(info.query, info.highlightRequireWhitespace);
        }
    }
}

// Search
//
var Search = {
    'window': window,
    'control': undefined,
    'loading': false,
    'query': '',
    'perform_with_delay_timeout': null,
    'connect_info': null
};

Search.SearchQueryHighlight = function (param_search_query, param_require_whitespace) {
    'use strict';

    var expressions, html_elements;

    // Remove highlights
    //
    Highlight.RemoveFromDocument(Search.window.document, 'search-result-highlight');

    // Highlight words
    //
    if (param_search_query !== undefined) {
        // Convert search query into expressions
        //
        expressions = SearchClient.SearchQueryToExpressions(param_search_query);

        // Apply highlights
        //
        Highlight.ApplyToDocument(Search.window.document, 'search-result-highlight', expressions, param_require_whitespace == true);
    }
};


// Highlights
//
var Highlight = {};

Highlight.ApplyToDocument = function (param_document, param_css_class, param_expressions, param_require_whitespace, param_handle_highlight) {
    'use strict';

    Browser.ApplyToTree(param_document.body, Highlight.TreeRecusionFilter,
        Highlight.TreeProcessTextNodesFilter,
        function (param_node) {
            var applied;

            applied = Highlight.Apply(param_document, param_css_class, param_expressions, param_require_whitespace, param_node);
            if ((applied) && (param_handle_highlight !== undefined)) {
                param_handle_highlight(param_node.parentNode);
            }
        });
};

Highlight.TreeProcessTextNodesFilter = function (param_node) {
    'use strict';

    var result = false;

    // Keep text nodes
    //
    if (param_node.nodeType === 3) {
        result = true;
    }

    return result;
};

Highlight.RemoveFromDocument = function (param_document, param_css_class) {
    'use strict';

    // Remove highlights
    //
    Browser.ApplyToTree(param_document.body, Highlight.TreeRecusionFilter,
        function (param_node) {
            var result;

            result = Highlight.TreeProcessHighlightSpansFilter(param_css_class, param_node);

            return result;
        },
        function (param_node) {
            Highlight.Remove(param_document, param_node);
        });
};

Highlight.TreeRecusionFilter = function (param_node) {
    'use strict';

    var result = false;

    // Recurse on content elements
    //
    if ((param_node.nodeType === 1) && (param_node.nodeName.toLowerCase() !== 'header') && (param_node.nodeName.toLowerCase() !== 'footer')) {
        result = true;
    }

    return result;
};

Highlight.TreeProcessHighlightSpansFilter = function (param_css_class, param_node) {
    'use strict';

    var result = false;

    // Find highlight spans
    //
    if ((param_node.nodeType === 1) && (param_node.nodeName.toLowerCase() === 'span') && (param_node.className === param_css_class)) {
        result = true;
    }

    return result;
};

Highlight.Apply = function (param_document, param_css_class, param_expressions, param_require_whitespace, param_node) {
    'use strict';

    var locations, result, location, highlight_node, span_element;

    locations = Highlight.MatchExpressions(param_expressions, param_require_whitespace, param_node.nodeValue);
    result = (locations.length > 0);
    while (locations.length > 0) {
        location = locations.pop();

        if ((location[0] + location[1]) < param_node.nodeValue.length) {
            param_node.splitText(location[0] + location[1]);
        }
        highlight_node = param_node.splitText(location[0]);
        span_element = param_document.createElement('span');
        //span_element.className = param_css_class;
		span_element.style.backgroundColor = "#a5ff06";
        param_node.parentNode.insertBefore(span_element, highlight_node);
        span_element.appendChild(highlight_node);
    }

    return result;
};

Highlight.Remove = function (param_document, param_node) {
    'use strict';

    var parent, previous, next, text, text_node;

    // Remove highlights
    //
    parent = param_node.parentNode;
    previous = param_node.previousSibling;
    next = param_node.nextSibling;
    text = '';
    if ((previous !== null) && (previous.nodeType === 3)) {
        text += previous.nodeValue;
        parent.removeChild(previous);
    }
    if ((param_node.childNodes.length > 0) && (param_node.childNodes[0].nodeType === 3)) {
        text += param_node.childNodes[0].nodeValue;
    }
    if ((next !== null) && (next.nodeType === 3)) {
        text += next.nodeValue;
        parent.removeChild(next);
    }
    text_node = param_document.createTextNode(text);
    parent.insertBefore(text_node, param_node);
    parent.removeChild(param_node);
};

Highlight.MatchExpression = function (param_expression, param_require_whitespace, param_string) {
    'use strict';

    var result, working_regexp, working_string, offset, match;

    result = [];

    // Find matches within the string in order
    //
    if (param_require_whitespace) {
        working_regexp = new RegExp('\\s' + param_expression + '\\s', 'i');
        working_string = ' ' + param_string + ' ';
    } else {
        working_regexp = new RegExp(param_expression, 'i');
        working_string = param_string;
    }
    offset = 0;
    match = working_regexp.exec(working_string);
    while (match !== null) {
        // Record location of this match
        //
        result.push([offset + match.index, match[0].length - ((param_require_whitespace) ? 2 : 0)]);

        // Advance
        //
        offset += match.index + match[0].length - ((param_require_whitespace) ? 1 : 0);
        working_regexp.lastIndex = 0;
        if (offset < working_string.length) {
            match = working_regexp.exec(working_string.substring(offset));
        } else {
            match = null;
        }
    }

    return result;
};

Highlight.MatchExpressions = function (param_expressions, param_require_whitespace, param_string) {
    'use strict';

    var result, match_locations, expression, index, alpha_locations, beta_locations, gamma_locations, start_index, alpha_location, beta_location, gamma_location;

    // Find all match locations
    //
    match_locations = [];
    for (index = 0; index < param_expressions.length; index += 1) {
        expression = param_expressions[index];

        match_locations[index] = Highlight.MatchExpression(expression, param_require_whitespace, param_string);
    }

    // Combine match locations
    //
    while (match_locations.length > 1) {
        alpha_locations = match_locations.pop();
        beta_locations = match_locations.pop();

        gamma_locations = [];
        start_index = -1;
        alpha_location = undefined;
        beta_location = undefined;
        while ((alpha_locations.length > 0) || (beta_locations.length > 0) || (alpha_location !== undefined) || (beta_location !== undefined)) {
            // Locate next location pair
            //
            while ((alpha_location === undefined) && (alpha_locations.length > 0)) {
                alpha_location = alpha_locations.shift();
                if (alpha_location[0] < start_index) {
                    alpha_location = undefined;
                }
            }
            while ((beta_location === undefined) && (beta_locations.length > 0)) {
                beta_location = beta_locations.shift();
                if (beta_location[0] < start_index) {
                    beta_location = undefined;
                }
            }

            // Pick a location
            //
            gamma_location = undefined;
            if ((alpha_location !== undefined) && (beta_location !== undefined)) {
                // Check start index
                //
                if (alpha_location[0] < beta_location[0]) {
                    // Use alpha
                    //
                    gamma_location = alpha_location;
                    alpha_location = undefined;
                } else if (alpha_location[0] > beta_location[0]) {
                    // Use beta
                    //
                    gamma_location = beta_location;
                    beta_location = undefined;
                } else {
                    // Check lengths (longer match wins)
                    //
                    if (alpha_location[1] > beta_location[1]) {
                        // Use alpha
                        //
                        gamma_location = alpha_location;
                        alpha_location = undefined;
                    } else if (alpha_location[1] < beta_location[1]) {
                        // Use beta
                        //
                        gamma_location = beta_location;
                        beta_location = undefined;
                    } else {
                        // Same location
                        //
                        gamma_location = alpha_location;
                        alpha_location = undefined;
                        beta_location = undefined;
                    }
                }
            } else {
                // Use the one that exists
                //
                if (alpha_location !== undefined) {
                    // Use alpha
                    //
                    gamma_location = alpha_location;
                    alpha_location = undefined;
                } else {
                    // Use beta
                    //
                    gamma_location = beta_location;
                    beta_location = undefined;
                }
            }

            // Track selected location
            //
            if (gamma_location !== undefined) {
                gamma_locations.push(gamma_location);
                start_index = gamma_location[0] + gamma_location[1];
            }
        }

        match_locations.push(gamma_locations);
    }

    result = match_locations[0];

    return result;
};


// Browser
//
var Browser = {};

Browser.ApplyToTree = function (param_element, param_recursion_filter, param_processing_filter, param_action) {
    'use strict';

    var index, child_node, queue;

    queue = [];
    for (index = 0; index < param_element.childNodes.length; index += 1) {
        child_node = param_element.childNodes[index];

        // Depth first processing
        //
        if (param_recursion_filter(child_node)) {
            // Recurse!
            //
            Browser.ApplyToTree(child_node, param_recursion_filter, param_processing_filter, param_action);
        }

        // Process?
        //
        if (param_processing_filter(child_node)) {
            // Add to queue
            //
            queue.push(child_node);
        }
    }

    // Process queue
    //
    for (index = 0; index < queue.length; index += 1) {
        child_node = queue[index];
        param_action(child_node);
    }
};


// SearchClient
//
var SearchClient = {};

SearchClient.ParseWordsAndPhrases = function (paramInput) {
    'use strict';

    var wordSplits, results, stringWithSpace, currentPhrase, currentWord, wordIndex, startQuotes;

    wordSplits = [];
    results = [];
    stringWithSpace = 'x x';
    currentPhrase = '';
    currentWord = '';
    wordIndex = 0;
    startQuotes = false;

    if (paramInput.length > 0) {
        wordSplits = paramInput.split(stringWithSpace.substring(1, 2));
        for (wordIndex = 0; wordIndex < wordSplits.length; wordIndex += 1) {
            currentWord = wordSplits[wordIndex];
            if (currentWord.length > 0) {
                // If the current word does not start with or end with a double quote
                // and a phrase has not been started, then add it to the result word list
                // and continue
                //
                if (currentWord.charAt(0) === '"') {
                    if (startQuotes) {
                        // This entry ends the current phrase and the word following
                        // the quote will be added as a separate word, unless there is
                        // a second quote at the start that will start a new phrase
                        //
                        results[results.length] = currentPhrase.substring(0, currentPhrase.length - 1);
                        currentPhrase = '';

                        while ((currentWord.length > 0) && (currentWord.charAt(0) === '"')) {
                            currentWord = currentWord.substring(1, currentWord.length);
                        }
                        if (currentWord.length > 0) {
                            currentPhrase += currentWord + ' ';
                        }
                    } else {
                        startQuotes = true;

                        // Strip off the leading quotes and process the word
                        //
                        while ((currentWord.length > 0) && (currentWord.charAt(0) === '"')) {
                            currentWord = currentWord.substring(1, currentWord.length);
                        }

                        if (currentWord.length > 0) {
                            // One Word Phrase - Add it as a word and set startQuotes to false
                            //
                            if (currentWord.charAt(currentWord.length - 1) === '"') {
                                startQuotes = false;
                                // Strip off trailing quotes and add it as a word
                                //
                                while ((currentWord.length > 0) && (currentWord.charAt(currentWord.length - 1) === '"')) {
                                    currentWord = currentWord.substring(0, currentWord.length - 1);
                                }

                                // Add the Word to the result array
                                //
                                results[results.length] = currentWord;
                            } else {
                                // The current word starts a phrase
                                //
                                currentPhrase += currentWord + ' ';
                            }
                        }
                    }
                } else if (currentWord.charAt(currentWord.length - 1) === '"') {
                    // Strip off trailing quotes regardless
                    //
                    while ((currentWord.length > 0) && (currentWord.charAt(currentWord.length - 1) === '"')) {
                        currentWord = currentWord.substring(0, currentWord.length - 1);
                    }

                    // Only process the word if the length is greater than 0 after
                    // stripping the trailing quotes
                    //
                    if (currentWord.length > 0) {
                        if (startQuotes) {
                            currentPhrase += currentWord;

                            results[results.length] = currentPhrase;
                            startQuotes = false;
                            currentPhrase = '';
                        } else {
                            // The phrase is not started
                            //
                            results[results.length] = currentWord;
                        }
                    }
                } else {
                    // The word is either a single word or in the middle of a phrase
                    //
                    if (startQuotes) {
                        currentPhrase += currentWord + ' ';
                    } else {
                        results[results.length] = currentWord;
                    }
                }
            }
        }
    }

    return results;
};

SearchClient.SearchReplace = function (paramString, paramSearchString, paramReplaceString) {
    'use strict';

    var  result, index;

    result = paramString;

    if ((paramSearchString.length > 0) && (result.length > 0)) {
        index = result.indexOf(paramSearchString, 0);
        while (index !== -1) {
            result = result.substring(0, index) + paramReplaceString + result.substring(index + paramSearchString.length, result.length);
            index += paramReplaceString.length;

            index = result.indexOf(paramSearchString, index);
        }
    }

    return result;
};

SearchClient.EscapeRegExg = function (param_string) {
    'use strict';

    var result;

    // Initialize result
    //
    result = param_string;

    // Escape special characters
    // \ . ? + - ^ $ | ( ) [ ] { }
    //
    result = SearchClient.SearchReplace(result, '\\', '\\\\');
    result = SearchClient.SearchReplace(result, '.', '\\.');
    result = SearchClient.SearchReplace(result, '?', '\\?');
    result = SearchClient.SearchReplace(result, '+', '\\+');
    result = SearchClient.SearchReplace(result, '-', '\\-');
    result = SearchClient.SearchReplace(result, '^', '\\^');
    result = SearchClient.SearchReplace(result, '$', '\\$');
    result = SearchClient.SearchReplace(result, '|', '\\|');
    result = SearchClient.SearchReplace(result, '(', '\\(');
    result = SearchClient.SearchReplace(result, ')', '\\)');
    result = SearchClient.SearchReplace(result, '[', '\\[');
    result = SearchClient.SearchReplace(result, ']', '\\]');
    result = SearchClient.SearchReplace(result, '{', '\\{');
    result = SearchClient.SearchReplace(result, '}', '\\}');

    // Windows IE 4.0 is brain dead
    //
    result = SearchClient.SearchReplace(result, '/', '[/]');

    // Convert * to .*
    //
    result = SearchClient.SearchReplace(result, '*', '.*');

    return result;
};

SearchClient.SearchQueryToExpressions = function (param_search_query) {
    'use strict';

    var result, prefix_expression, suffix_expression, words_and_phrases, index, word_or_phrase, expression;

    result = [];
    prefix_expression = '[\u201C\u201D\u0022\u0027\u2018\u2019]?';
    suffix_expression = '[\\?\\.,:\u201C\u201D\u0022\u0027\u2018\u2019]?';
    if (param_search_query !== undefined) {
        words_and_phrases = SearchClient.ParseWordsAndPhrases(param_search_query);
        for (index = 0; index < words_and_phrases.length; index += 1) {
            word_or_phrase = words_and_phrases[index];

            // Avoid highlighting everything
            //
            if (word_or_phrase !== '*') {
                expression = SearchClient.EscapeRegExg(word_or_phrase);
                expression = SearchClient.SearchReplace(expression, '.*', '\\S*');
                expression = prefix_expression + expression + suffix_expression;
                result.push(expression);
            }
        }
    }

    return result;
};
