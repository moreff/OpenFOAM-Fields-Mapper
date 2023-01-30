# OpenFOAM-Fields-Mapper
The codes I used to initialize 1d/2d planar and spherical flames

# Usage  
An example with cavity tutorial case:  
```shell
# Don't forget to source OpenFOAM's bashrc with the version you want to use
run
cp -r $FOAM_TUTORIALS/incompressible/icoFoam/cavity/cavity/ .
cd cavity
blockMesh
git clone git@github.com:moreff/OpenFOAM-Fields-Mapper.git
cp OpenFOAM-Fields-Mapper/U.template 0/U
cp OpenFOAM-Fields-Mapper/U.dat 0/
cp OpenFOAM-Fields-Mapper/OpenFOAMfieldsMapperDict system/
paraFoam
```

The last command opens paraview, where you can visualize the mapping result (U field).  
Then you can play around with values in `OpenFOAMfieldsMapperDict` and update the mapping results using `refresh` button
