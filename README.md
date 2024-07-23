# Nvidia-OrinX Drive Demo

## introduce
The NVIDIA DRIVE® OS 6.0 Linux Software Development Kit enables application development with NVIDIA DRIVE Orin™ SoC for Automotive. At a high level.
Platform Software Stacks as follow
![alt text](doc/driveos_605x/NVIDIA_DRIVE_OS_6.0.5_Linux_SDK_Developer_Guide/common/graphics/archi/archi_drive_os_image2.png)

## Foundation Services Stack
The NVIDIA DRIVE AGX™ platform Foundation services runtime software stack provides the infrastructure for all the components of the platform
![alt text](doc/driveos_605x/NVIDIA_DRIVE_OS_6.0.5_Linux_SDK_Developer_Guide/common/graphics/archi/archi_foundation_image3.png)

## PART I DriveOS SDK

### nvsipl_camera
├── CAutoRecovery.hpp
├── CCmdLineParser.hpp
├── CComposite.cpp
├── CCompositeHelper.hpp
├── CComposite.hpp
├── CCompositeNvSci.cpp
├── CCompositeNvSci.hpp
├── CFileReader.hpp
├── CFileWriter.hpp
├── CFrameFeeder.hpp
├── CNvSIPLConsumer.hpp
├── CNvSIPLMaster.hpp
├── CNvSIPLMasterNvSci.hpp
├── CNvWfd.cpp
├── CNvWfd.hpp
├── CProfiler.hpp
├── CUtils.cpp
├── CUtils.hpp
├── main.cpp
└── Makefile
### ijpg_encoder
├── cmdline.c
├── cmdline.h
├── image_jpegenc.c
├── Makefile
└── nvm_ijpe_sci
### nvscistream_event
├── 00README.txt
├── block_c2c.c
├── block_common.c
├── block_consumer_uc1.c
├── block_consumer_uc2.c
├── block_info.h
├── block_ipc.c
├── block_limiter.c
├── block_multicast.c
├── block_pool.c
├── block_presentsync.c
├── block_producer_uc1.c
├── block_producer_uc2.c
├── block_queue.c
├── block_returnsync.c
├── event_loop.h
├── event_loop_service.c
├── event_loop_threads.c
├── main.c
├── Makefile
├── usecase1.h
├── usecase2.h
├── util.c
└── util.h
### dla_sample
├── cmdline
│   ├── cmdParser.cpp
│   └── cmdParser.h
├── dla
│   ├── dla.cpp
│   └── dla.h
├── logging
│   ├── cLogger.cpp
│   └── cLogger.h
├── main.cpp
├── Makefile
├── scisync
│   ├── sciSync.cpp
│   └── sciSync.h
├── tensor
│   ├── tensor.cpp
│   └── tensor.h
├── testMT.cpp
├── testMT.h
├── testRuntime.cpp
├── testRuntime.h
├── testSciSync.cpp
├── testSciSync.h
└── utils
    ├── utils.cpp
    └── utils.h

## PART II Driveworks

### driveworks-5.8

```sh
driveworks_5.8.82-317146970_amd64.deb
driveworks-samples_5.8.82-317146970_amd64.deb
driveworks-cgf_5.8.82-317146970_amd64.deb
driveworks-cgf-samples_5.8.82-317146970_amd64.deb
driveworks-cgf-doc_5.8.82-317146970_all.deb
driveworks-stm_5.8.82-317146970_amd64.deb
driveworks-stm-samples_5.8.82-317146970_amd64.deb

# driveworks-cgf-ui_5.8.82-317146970_amd64.deb
# driveworks-data_5.8.82-317146970_all.deb
```

### driveworks-5.10

```sh
driveworks_5.10.87-323457480_amd64.deb
driveworks-samples_5.10.87-323457480_amd64.deb
# driveworks-doc_5.10.87-323457480_all.deb
# cgf not found
# stm
driveworks-stm_5.10.87-323457480_amd64.deb
```

### 拷贝方法

```sh
# 多线程压缩解压缩
sudo apt install pigz

cd /gw_demo
tar --use-compress-program=pigz -h -cvpf  driveworks-5.10.tar.gz /usr/local/driveworks/*

tar --use-compress-program=pigz -xvpf driveworks-5.10.tar.gz
```
