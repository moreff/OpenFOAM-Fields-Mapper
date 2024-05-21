# OpenFOAM-Fields-Mapper
Functions, mapping 1d fields, defined in a text file, to OpenFOAM fields

# Usage  
An example with cavity tutorial case:  
```shell
# Don't forget to source OpenFOAM's bashrc with the version you want to use
run
cp -r $FOAM_TUTORIALS/incompressible/icoFoam/cavity/cavity/ .
cd cavity
blockMesh
git clone https://github.com/moreff/OpenFOAM-Fields-Mapper.git
cp OpenFOAM-Fields-Mapper/U.template 0/U
cp OpenFOAM-Fields-Mapper/U.dat 0/
cp OpenFOAM-Fields-Mapper/OpenFOAMfieldsMapperDict system/
paraFoam
```

The last command opens Paraview, where you can visualize the mapping result (U field).  
Then you can play around with values in `OpenFOAMfieldsMapperDict` and update the mapping results using `refresh` button
