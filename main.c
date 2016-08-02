/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: nuno
 *
 * Created on August 1, 2016, 7:50 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"

/*
 * 
 */
int main(int argc, char** argv) {

    struct topology * tp = (struct topology *) malloc(sizeof (struct topology));

    tp->hidden_neurons = 5;
    tp->in_neurons = 3;
    tp->layers = 3;
    tp->out_neurons = 3;

    struct net* my = initializeNet(tp);

    int train_X[3] = {1, 1, 1};
    
     printNet(my);
    
    feedFoward(my,train_X,3);

   


    return (EXIT_SUCCESS);
}



