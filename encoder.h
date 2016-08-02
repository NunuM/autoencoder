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

    
#define TOTAL_LAYERS 3
    
    struct topology {
        uint layers;
        uint in_neurons;
        uint out_neurons;
        uint hidden_neurons;
    };


    struct neuron {
        double weight;
        double deltaWeight;
        double outPut;
        double gradient;
        double bias;
        double z;
    };

    struct layer {
        struct neuron *neurons;
    };
    
    struct net {
        struct layer * layers;
        struct topology * p_topology;
    };

   
    double sigmoid(double x);
    struct net * initializeNet(struct topology *p_topology);
    void printNet(struct net * p_net);
    int feedFoward(struct net * p_net, int * input, int lenght);
    
    
    

#ifdef __cplusplus
}
#endif

#endif /* ENCODER_H */

