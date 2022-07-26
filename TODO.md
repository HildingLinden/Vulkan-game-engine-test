# TODO
## Features
- Shadow maps
- Cascaded shadow maps
- Multithreading- / command buffer generation
- Instanced rendering - Indirect drawing
- Dynamic uniforms
- Separate images and sampler descriptors
- Pipeline cache
- Push constants
- Rat tracing
- Multiple subpasses
- Occlusion querying
- Pipeline statistics
- PBR
- Deferred rendering
- Cull and LOD on GPU

## Misc improvements
- Fix stack trashed after resizing and closing window
- Add GPU performance timing with TimeStamp/performance query
- See vk_layer_settings.txt in config folder of vulkan sdk for more layer config options
- Try to find a queueFamily that has both graphics and present 
- Display available presentationModes
- Post-processing with different swapchain imageUsage
- Use libshaderc to compile shaders programatically or atleast build event in visual studio
- Modernize readfile?
- Ability to choose between different multisamplings in graphicsPipeline
- Create separate commandPool for copying buffers?
- Use vkWaitForFences in copyBuffer to be able to schedule multiple copies at the same time
- Use VulkanMemoryAllocator library instead of allocating memory for each individual buffer
- Bind all vertex buffers in one big buffer
- Combine all operations in createMaterial to one commandBuffer to improve performance insttead of synchronously executing them, (see https://vulkan-tutorial.com/en/Texture_mapping/Images#page_Transition-barrier-masks)
- Query for device limits for anisotropicFiltering and others and save to global for using in createSampler
- Create depthBufferImage for each image in flight?
- Add Vulkan raii or Vulkan unique handles
- Switch to SDL2?
- Test difference between storeOp store & don care on color attachment and depth attachment (with VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)