
#pragma once

#include <string>


struct T {
    int v;
    int min;
    int max;
    int step;

    std::string name;
};


struct SearchParameters {

    //                             v   min  max step        name
    T LMR_divisor_quiet       = { 230, 150, 230, 20, "LMR_divisor_quiet"};
    T LMR_base_quiet          = { 140, 100, 170, 20, "LMR_base_quiet"};
    T LMR_history_divisor     = {10000, 4000, 14000, 1000, "LMR_history_divisor"};

    T RFP_depth               = {   7,   5,  11,   2, "RFP_depth"};
    T RFP_margin              = { 110,  50, 200,  30, "RFP_margin"};

    T LMP_depth               = {   4,   1,   5,   1, "LMP_depth"};
    T LMP_margin              = {  10,   5,  15,   1, "LMP_margin"};

    T history_pruning_depth   = {  10,   3,  20,   2, "history_pruning_depth"};
    T history_pruning_divisor = {9600, 1000, 20000, 1800, "history_pruning_divisor"};

    T NMP_depth               = {   1,   0,   4,   1, "NMP_depth"};
    T NMP_base                = {   5,   1,   5,   1, "NMP_base"};
    T NMP_depth_divisor       = {   4,   2,   6,   1, "NMP_depth_divisor"};
    T NMP_eval_divisor        = { 400, 100, 400,  40, "NMP_eval_divisor"};
    T NMP_condition_base      = { 128,   0, 200,  10, "NMP_condition_base"};
    T NMP_condition_depth     = {  11,   0,  20,   2, "NMP_condition_depth"};
    T NMP_condition_improving = {   3,   0,  20,   2, "NMP_condition_improving"};

    T SEE_base_depth          = {   2,   1,  10,   1, "SEE_base_depth"};
    T SEE_noisy_depth         = {   0,   0,   4,   1, "SEE_noisy_depth"};
    T SEE_pv_depth            = {   5,   0,   5,   1, "SEE_pv_depth"};
    T SEE_base_moves          = {   4,   1,   5,   1, "SEE_base_moves"};
    T SEE_base_history        = {5800, 1000, 10000, 1000, "SEE_base_history"};
    T SEE_quiet_multiplier    = {  40,  20,  80,   8, "SEE_quiet_multiplier"};
    T SEE_noisy_multiplier    = {  85,  50, 150,  10, "SEE_noisy_multiplier"};

    T SEE_MO_threshold        = {  85,  60, 120,   5, "SEE_MO_threshold"};

    T LMP_margin_quiet        = {   2,   1,   4,   1, "LMP_margin_quiet"};

    T FP_depth                = {   7,   1,   8,   1, "FP_depth"};
    T FP_multiplier           = { 170,  80, 220,  20, "FP_multiplier"};
    T FP_margin               = {  70,  40, 150,  20, "FP_margin"};

    T QSEE_base               = {  70,  40, 200,  10, "QSEE_base"};

    T IIR_base_depth          = {   4,   1,   8,   1, "IIR_base_depth"};

    T SE_base_depth           = {   6,   3,   9,   1, "SE_base_depth"};
    T SE_dext_margin          = {  12,   6,  25,   2, "SE_dext_margin"};
    T SE_dext_limit           = {   7,   4,  12,   1, "SE_dext_limit"};

    T deeper_margin           = {  80,  50, 130,   8, "deeper_margin"};

    T ASP_beta_scaler         = {   5,   1,  10,   1, "ASP_beta_scaler"};
    T ASP_alpha_scaler        = {   3,   1,  10,   1, "ASP_alpha_scaler"};
    T ASP_delta_scaler        = {   2,   1,  10,   1, "ASP_delta_scaler"};
    T ASP_delta_divisor       = {   5,   1,  10,   1, "ASP_delta_divisor"};
    T ASP_delta_min           = {   9,   4,  15,   1, "ASP_delta_min"};

    T H_max_quiet             = {  9000, 5000, 18000, 600, "H_max_quiet"};
    T H_max_noisy             = { 12000, 5000, 18000, 600, "H_max_noisy"};
    T H_max_cont              = { 11000, 5000, 18000, 600, "H_max_cont"};

    T TM_node_margin          = { 135, 100, 200,   8, "TM_node_margin"};
    T TM_node_scalar          = { 180, 140, 200,   6, "TM_node_scalar"};

    T TM_score_min            = { 276, 100, 500,  30, "TM_score_min"};
    T TM_score_max            = { 136,  50, 400,  30, "TM_score_max"};
    T TM_score_base           = {  98,  70, 100,   5, "TM_score_base"};
    T TM_score_divisor        = { 381, 150, 500,  25, "TM_score_divisor"};

    T TM_hard_scalar          = { 281, 150, 400,  20, "TM_hard_scalar"};
    T TM_soft_scalar          = {  78,  40, 150,  10, "TM_soft_scalar"};


    T* all_parameters[50] = {
            &LMR_divisor_quiet,
            &LMR_base_quiet,
            &LMR_history_divisor,

            &RFP_depth,
            &RFP_margin,

            &LMP_depth,
            &LMP_margin,

            &history_pruning_depth,
            &history_pruning_divisor,

            &NMP_depth,
            &NMP_base,
            &NMP_depth_divisor,
            &NMP_eval_divisor,
            &NMP_condition_base,
            &NMP_condition_depth,
            &NMP_condition_improving,

            &SEE_base_depth,
            &SEE_noisy_depth,
            &SEE_pv_depth,
            &SEE_base_moves,
            &SEE_base_history,
            &SEE_quiet_multiplier,
            &SEE_noisy_multiplier,

            &SEE_MO_threshold,

            &LMP_margin_quiet,

            &FP_depth,
            &FP_multiplier,
            &FP_margin,

            &QSEE_base,

            &IIR_base_depth,

            &SE_base_depth,
            &SE_dext_margin,
            &SE_dext_limit,

            &deeper_margin,

            &ASP_beta_scaler,
            &ASP_alpha_scaler,
            &ASP_delta_scaler,
            &ASP_delta_divisor,
            &ASP_delta_min,

            &H_max_quiet,
            &H_max_noisy,
            &H_max_cont,

            &TM_node_margin,
            &TM_node_scalar,

            &TM_score_min,
            &TM_score_max,
            &TM_score_base,
            &TM_score_divisor,

            &TM_hard_scalar,
            &TM_soft_scalar
    };
};


inline SearchParameters search_params{};
