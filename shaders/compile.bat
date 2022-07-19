set "var=shader"
set /p "var=[%var%] "
E:\VulkanSDK\1.3.216.0\Bin\glslc.exe %var%.vert -O -o %var%Vert.spv
E:\VulkanSDK\1.3.216.0\Bin\glslc.exe %var%.frag -O -o %var%Frag.spv
pause