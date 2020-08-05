# TODO
## Graphics engine
### Misc
- Faster UBO/SSBO updates by partially updating buffers/memory
- Dynamically scale size of UBO/SSBO
	- createDescriptorSets
	- createShaderBuffer
	- addRects? to set the new pointers
- Reuse Vertex/Index buffers
- Can swapchainImage count can change when recreating swapchain?
- TimeStamp/performance query
- Refactor ghraphics engine into components
- Multithreading
- Materials (texture referece, sampler, material specific values)
- UBO descriptor set per mesh
- Use separate buffers for position, texture coordinates, color etc. instead of one unified vertex buffer?
### 2D
- Drawing different geometries
### 3D
- Multisampling
- Mipmaps
- Shadow maps
- Loading models
## Physcics engine
- Broad phase collision detection
- SAT collision detection
- Diagonal collision detection