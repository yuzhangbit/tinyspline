/* Copyright (c) 2018, Yu Zhang, Intelligent Vehicle Research Center(IVRC), 
 * Beijing Institute of Technology.
 * All rights reserved.
 *        Files: tinyspline_c_tests.cpp
 *   Created on: 08, 04, 2018 
 *       Author: Yu Zhang
 *        Email: yu.zhang.bit@gmail.com
 */


#include "gtest/gtest.h"
#include <tinyspline.h>
#include <tinysplinecpp.h>
#include <vector>
#include <iostream>
#include <fstream>

TEST(TSplineTests, natural_cubic_spline) {
    double xs[9] = {0, 1, 2, 5, 8, 14, 16, 18, 22};
    double ys[9] = {0, 5, 10, 12, 10, -10, -12, -10, 0};
    
    tsReal pts[18] = {0, 0,
                      1, 5,
                      2, 10,
                      5, 12,
                      5.5, 10,
                      14, -10,
                      16, -12,
                      18, -10,
                      22, 0};
    tsBSpline spline = {};
    tsDeBoorNet net;
    tsReal *result;
    tsReal *ctrlp, *knots;
    std::size_t n_pts = 500;
    tsError ret = ts_bspline_interpolate_cubic(pts, 9, 2, &spline);
    std::ofstream myfile, ctrlp_file, knots_file;
    myfile.open ("cs_xy.csv");
    ctrlp_file.open("cs_ctrlp.csv");
    knots_file.open("cs_knots.csv");
    ts_bspline_control_points(&spline, &ctrlp);
    ts_bspline_knots(&spline, &knots);
    std::size_t n_knots = ts_bspline_num_knots(&spline);
    myfile << "x" << ";" << "y" << std::endl;
    for (std::size_t i = 0; i <= n_pts; i++) {
        double u = i * 1.0 / n_pts;
        ts_bspline_eval(&spline, u, &net);
        ts_deboornet_result(&net, &result);
        myfile << result[0] << ";" << result[1] << std::endl;
    }
    ctrlp_file << "x" << ";" << "y" << std::endl;
    for (std::size_t i = 0; i < 9; i++) {
        ctrlp_file << ctrlp[2*i] << ";" << ctrlp[2*i+1] << std::endl;
    }
    std::cout << "knots num:" << ts_bspline_num_knots(&spline) << std::endl;
    for (std::size_t i = 0; i < 36; i++) {
        std::cout << knots[i] << std::endl;
    }
    knots_file << "knots" << std::endl;
    for (std::size_t i = 0; i < ts_bspline_num_knots(&spline); i++) {
        knots_file << knots[i] << std::endl;
    }
    knots_file.close();
    ctrlp_file.close();
    myfile.close();
    
    // clean up
    ts_deboornet_free(&net);
    // delete pointers
    delete result, ctrlp, knots;
    result = nullptr;
    ctrlp = nullptr;
    knots = nullptr;
    ts_bspline_free(&spline);
}

TEST(TSplineTests, bspline) {
    tinyspline::BSpline spline(9);
    tsReal pts[18] = {0, 0,
                      1, 5,
                      2, 10,
                      5, 12,
                      8, 10,
                      14, -10,
                      16, -12,
                      18, -10,
                      22, 0};
    std::vector<tinyspline::real> ctrlp = spline.controlPoints();
    std::cout << "control points size:" << ctrlp.size() << std::endl;
    for (std::size_t i = 0; i < ctrlp.size(); i++) {
        ctrlp[i] = pts[i];
    }
    spline.setControlPoints(ctrlp);
    std::vector<tinyspline::real> result;
    
    std::ofstream myfile;
    myfile.open ("bs_xy.csv");
    std::size_t n_pts = 500;
    myfile << "x" << ";" << "y" << std::endl;
    for (std::size_t i = 0; i <= n_pts; i++) {
        double u = i * 1.0 / n_pts;
        result = spline.eval(u).result();
        myfile << result[0] << ";" << result[1] << std::endl;
    }
    myfile.close();
    

}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}