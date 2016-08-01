/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: bullet
 *
 * Created on August 1, 2016, 3:26 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"
/*
 * 
 */
int main(int argc, char** argv) {
    
    struct topology tp;
    
    tp.input = 5;
    tp.hiddenLayer = 5;
    tp.outPutLayer = 5;
    
    
    struct net* myNet = initializeNet(&tp);
    
    
    
    
    
    
    
    return (EXIT_SUCCESS);
}

