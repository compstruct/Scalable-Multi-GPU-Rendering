The appetite for higher and higher 3D graphics quality continues to drive GPU computing requirements. To satisfy these demands, GPU vendors are moving towards new architectures, such as MCM-GPU and multi-GPUs, that connect multiple chip modules or GPUs with high-speed links (e.g., NVLink and XGMI) to provide higher computing capability.

Unfortunately, it is not clear how to adequately parallelize the rendering pipeline to take advantage of these resources while maintaining low rendering latencies. Current implementations of Split Frame Rendering (SFR) are bottlenecked by redundant computations and sequential inter-GPU synchronization, and fail to scale as the GPU count increases.

In this paper, we propose CHOPIN, a novel SFR scheme for multi-GPU systems that exploits the parallelism available in image composition to eliminate the bottlenecks inherent to existing solutions. CHOPIN composes opaque sub-images out-of-order, and leverages the associativity of image composition to compose adjacent sub-images of transparent objects asynchronously. To mitigate load imbalance across GPUs and avoid inter-GPU network congestion, CHOPIN includes two new scheduling mechanisms: a draw-command scheduler and an image composition scheduler. Detailed cycle-level simulations on eight real-world game traces show that, in an 8-GPU system, CHOPIN offers speedups of up to 1.56× (1.25× gmean) compared to the best prior SFR implementation.

# Paper Link

CHOPIN: Scalable Graphics Rendering in Multi-GPU Systems via Parallel Image Composition, in HPCA-2021 (to appear).

# Multi-GPU-ATTILA

This work was implemented upon [ATTILA](http://attila.ac.upc.edu/wiki/index.php/Attila_Project). The original README of the ATTILA that we used can be found at [here](./multigpu_graphics_attila/README).

For multi-GPU graphics rendering, our baseline implementation is to duplicate all primitives in every GPU. We also implemented both [GPUpd](https://dl.acm.org/doi/abs/10.1145/3123939.3123968?casa_token=rB2k2gbD9_QAAAAA:ejh8sFOZK2KGL5hwQzCzfyS4025Z1nT2C4wZ0qNUhAvVYtiHSGjwvfRN_4fqOEJYFhY1ppxXiyezYw) and CHOPIN.

A template config for multi-GPU simulation can be found at [here](./multigpu_graphics_attila/test/config/bGPU_MultiGPUs.ini). All benchmarks that we used can be downloaded from [here](http://attila.ac.upc.edu/traceList/).

# ParKD

In CHOPIN, we use [ParKD](https://github.com/bchoi/ParKD) to divide draw calls into multiple groups, and partition transparent draw calls among GPUs. The original README of the ParKD that we used can be found at [here](./ParKD/README).

Before running ParKD, you should run ATTILA first with single-GPU configuration and profileForSortLast being enabled. The generated profiling results (inputVertexes.obj, blendInfo.obj, zTestInfo.obj, and zFightingInfo.obj) are inputs of ParKD. The binary output file of ParKD will then be used as an input of CHOPIN simulation in ATTILA.
