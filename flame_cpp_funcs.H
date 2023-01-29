#ifndef flame_cpp_funcs_H
#define flame_cpp_funcs_H

#include <fstream>
#include <vector>

void read_2_column_data_file(const string& filename, std::vector<float>& xc, std::vector<float>& Yc,
    bool limitMaxVal=false, float maxVal=1, bool limitMinVal=false, float minVal=0) {
    // Reading cantera data file
    // ifstream dataFile(dict.name() + ".dat");
    ifstream dataFile(filename);
    if (! dataFile.is_open()){
        FatalErrorInFunction
            << "Cannot open file " << filename
            << exit(FatalError);
        // Info << "E: Data file " + filename + " is not open!" << endl;
    }
    // std::vector<float> xc, Yc;
    float a, b;
    while(!dataFile.eof()) {
        dataFile >> a;
        if(dataFile.eof()) {
            // Info << "WARNING: unexpected EOF" << endl;
            break;
        }
        dataFile >> b;
        // Info << a << ": " << b << endl;
        if (xc.size() > 0 && xc.back() >= a) {
            Info << "WARNING: x coordinates are not in ascending order: "
                   << xc.back() << ", " << a << " in file " + filename << endl;
        }
        if (limitMinVal&&(b < minVal)) {
            Info << "WARNING: Value lower than limit " << minVal <<" encounetered: "
                   << b << " in file " + filename << endl;
            Info << "    setting to " << minVal << endl;
            b = minVal;
        } else if (limitMaxVal&&(b > maxVal)) {
            Info << "WARNING: Value larger than limit " << maxVal <<" encounetered: "
                   << b << " in file " + filename << endl;
            Info << "    setting to " << maxVal << endl;
            b = maxVal;
        }
        xc.push_back(a);
        Yc.push_back(b);
    }
    return;
}

float interpolate(const std::vector<float>& xc, const std::vector<float>& Yc, const float x){
    std::vector<float>::const_iterator it = std::find_if(xc.begin(),xc.end(),[x](const float& a){return a > x;});
    float result;
    size_t i_greater = it-xc.begin();
    if (i_greater > 0) {
        if (i_greater >= xc.size()) {
            result = Yc[xc.size()-1];
        } else {
            size_t i_lower = i_greater-1;
            float x0 = xc[i_lower];
            float x1 = xc[i_greater];
            result = Yc[i_lower] + (x-x0)/(x1-x0)*(Yc[i_greater]-Yc[i_lower]);
        }
    } else {
        result = Yc[0];
    }
    return result;
}

#endif
