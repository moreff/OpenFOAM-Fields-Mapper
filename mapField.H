mappedField #codeStream
{
    codeInclude
    #{
        #include "fvCFD.H"
        #include <vector>
        #include "flame_cpp_funcs.H"

    #};
    codeOptions
    #{
        -I$(LIB_SRC)/finiteVolume/lnInclude \
        -I$(LIB_SRC)/meshTools/lnInclude \
        -I$(FOAM_CASE)/OpenFOAM-Fields-Mapper
    #};
    codeLibs
    #{
        -lmeshTools \
        -lfiniteVolume
    #};
    code
    #{
        const IOdictionary& d = static_cast<const IOdictionary&>(dict);
        dictionary config(IFstream("system/OpenFOAMfieldsMapperDict")());

        const word mode = config.lookup<word>("mode");
        Info << mode << endl;
        if ((mode != "planar")&&(mode != "spherical")) {
            FatalIOErrorInFunction
            (
                config
            )   << "Mode options are planar/spherical"
                << exit(FatalIOError);
        }

        const Switch inverseData = config.lookupOrDefault<Switch>("inverseData", false);
        const scalar centerOfData = config.lookupOrDefault<scalar>("centerOfData", 0.0);
        const vector mappingOrigin = config.lookupOrDefault<vector>("mappingOrigin", vector(0.,0.,0.));
        vector directionOfMapping = config.lookupOrDefault<vector>("directionOfMapping", vector(0.,0.,0.));
        const word fieldType = d.headerClassName();

        if (mag(directionOfMapping) == 0) {
          FatalIOErrorInFunction
          (
              config
          )   << "directionOfMapping cannot be a zero-vector"
              << exit(FatalIOError);
        } else {
            directionOfMapping = directionOfMapping/mag(directionOfMapping); // normalize
        }

        std::vector<float> datax, datay;
        read_2_column_data_file(dict.name()+".dat", datax, datay);
        // ---=== Finished reading inputs ====---

        const fvMesh& mesh = refCast<const fvMesh>(d.db());
        scalarField Yscal(mesh.nCells(), 0.0);
        vectorField Yvec(mesh.nCells(), vector(0.,0.,0.));

        forAll(Yscal, i)
        {
            vector distanceV = mesh.C()[i]-mappingOrigin;
            scalar distance = (mode=="planar")?
                              directionOfMapping&distanceV
                              :
                              mag(mesh.C()[i]-mappingOrigin);

            scalar convertedDistance = (inverseData?-1:1)*distance+centerOfData;
            float val = interpolate(datax, datay, convertedDistance);
            if (fieldType == "volVectorField"){
                Yvec[i] = (mode=="planar")?
                val*directionOfMapping
                :
                val*(distanceV/mag(distanceV));
            } else if (fieldType == "volScalarField"){
                Yscal[i] = val;
            }
        }

        if (fieldType == "volVectorField"){
            os << Yvec;
        } else if (fieldType == "volScalarField"){
            os << Yscal;
        }

    #};

};
