/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   enconder.c
 * Author: bullet
 *
 * Created on August 1, 2016, 3:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"

/*
 * 
 */


struct net * initializeNet(struct topology *p_topology) {

    if (p_topology == NULL)
        return NULL;


    struct net* p_net = (struct net *) malloc(sizeof (struct net));

    if (p_net == NULL) {
        return NULL;
    }
    
    p_net->layers = (struct layer *) malloc( (sizeof (struct layer) * TOTAL_LAYERS ));


    int i;

    p_net->layers->neurons = (struct neuron *) malloc(sizeof (struct neuron) * p_topology->input);
    (++p_net->layers)->neurons = (struct neuron *) malloc(sizeof (struct neuron) * p_topology->hiddenLayer);
    (++p_net->layers)->neurons = (struct neuron *) malloc(sizeof (struct neuron) * p_topology->outPutLayer);

    

    /**
     * Array indexing, also this can be done by pointer arithmetic 
     */
    

    return p_net;
}



void printNet(struct net * p_net){
    
    
    
    
}