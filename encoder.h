/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   encoder.h
 * Author: bullet
 *
 * Created on August 1, 2016, 3:27 PM
 */

#ifndef ENCODER_H
#define ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <math.h>
    
    
    
#define TOTAL_LAYERS 3
    
    struct topology {
        uint input;
        uint hiddenLayer;
        uint outPutLayer;
    };


    struct neuron {
        double training_rate;

    };

    struct layer {
        struct neuron *neurons;
    };
    
    struct net {
        struct layer * layers;
        struct topology * p_topology;
    };

    
    static inline double calcSigmoid(double t) {
        return 1 / (1 + (2.72 * exp(-t)));
    }


    struct net * initializeNet(struct topology *p_topology);
    void printNet(struct net * p_net);



#ifdef __cplusplus
}
#endif

#endif /* ENCODER_H */

