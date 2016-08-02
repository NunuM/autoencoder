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
#include <time.h>
#include <math.h>

/*
 * 
 */


struct net * initializeNet(struct topology *p_topology) {

    time_t t;
    srand((unsigned) time(&t));

    if (p_topology == NULL)
        return NULL;

    struct net* p_net = (struct net *) malloc(sizeof (struct net));

    p_net->p_topology = p_topology;

    if (p_net == NULL) {
        return NULL;
    }

    p_net->layers = (struct layer *) malloc((sizeof (struct layer) * p_topology->layers));


    if (p_net->layers == NULL)
        return NULL;


    p_net->layers->neurons = (struct neuron *) malloc(sizeof (struct neuron) * p_topology->in_neurons);


    int i, j;
    int hidden_num = p_topology->layers - 2;

    for (i = 0; i < hidden_num; i++) {

        (p_net->layers + (i + 1))->neurons = (struct neuron *) malloc(sizeof (struct neuron) * p_topology->hidden_neurons);

        if ((p_net->layers + (i + 1))->neurons == NULL) {
            return NULL;
        }
        //Initialize weights
        for (j = 0; j < p_topology->hidden_neurons; j++) {
            ((p_net->layers + (i + 1))->neurons + j)->weight = ((double)rand()/(double)RAND_MAX);
            ((p_net->layers + (i + 1))->neurons + j)->bias = 1;
        }
    }


    (p_net->layers + (p_topology->layers - 1))->neurons = (struct neuron *) malloc(sizeof (struct neuron) * p_topology->out_neurons);


    if ((p_net->layers + (p_topology->layers - 1))->neurons == NULL) {
        return NULL;
    }


    for (i = 0; i < p_topology->out_neurons; i++) {
        ((p_net->layers + (p_topology->layers - 1))->neurons + i)->weight = rand() % 100;
        ((p_net->layers + (p_topology->layers - 1))->neurons + i)->bias = 1;
    }

    return p_net;
}

int feedFoward(struct net * p_net, int * input, int lenght) {

    unsigned int i, total_hidden_layers, j, k;
    double sum = 0.0;

    uint total_hidden_neurons = p_net->p_topology->hidden_neurons;
    for (i = 0; i < lenght; i++) {
        (p_net->layers->neurons + i)->outPut = *(input + i);
    }

    total_hidden_layers = p_net->p_topology->layers - 2;




    for (j = 0; j < total_hidden_neurons; j++) {
        for (k = 0; k < p_net->p_topology->in_neurons; k++) {
            double out = (p_net->layers->neurons + k)->outPut;
            double w = ((p_net->layers + 1)->neurons + j)->weight;
            double b = ((p_net->layers + 1)->neurons + j)->bias;
            sum += (out * w) + b;
        }
        ((p_net->layers + 1)->neurons + j)->z = sigmoid(sum);
    }



    for (j = 0; j < p_net->p_topology->out_neurons; j++) {
        for (k = 0; k < total_hidden_neurons; k++) {
            double out = (p_net->layers->neurons + 1)->outPut;
            double w = ((p_net->layers + 2)->neurons + j)->weight;
            double b = ((p_net->layers + 2)->neurons + j)->bias;
            sum += (out * w) + b;
        }
        ((p_net->layers + 2)->neurons + j)->z = sigmoid(sum);
    }


    return EXIT_SUCCESS;
}

void printNet(struct net * p_net) {

    puts("***************hidden data***********");
    int total_layers = p_net->p_topology->layers - 2;
    int neuron_per_layer = p_net->p_topology->hidden_neurons;
    struct layer* pt_hidden_base = (p_net->layers + 1);

    int i, j;
    for (i = 0; i < total_layers; i++) {
        for (j = 0; j < neuron_per_layer; j++) {
            double training_rate = ((pt_hidden_base + i)->neurons + j)->weight;
            printf("%f---", training_rate);
        }
        printf("\n");
    }

}

double sigmoid(double x) {

    double return_value;

    return_value = 1 / (1 + exp(-x));

    return return_value;
}

void printLayer(const struct layer * pt_layer) {

    int i, size = pt_layer->size;

    for (i = 0; i < size; i++) {
        printf("%d neuron has output of:%f\n", i + 1, (pt_layer->neurons + i)->z);
    }

}

struct layer * getEncondedData(struct net * pt_net) {
    return (pt_net->layers + 1);
}

struct layer * getDecodedData(struct net * pt_net) {
    return (pt_net->layers + 2);
}

int backFoward(struct net * pt_net,  int * target, int lenght) {



    struct layer* firstLayer = (pt_net->layers + 0);
    struct layer* outPutLayer = (pt_net->layers + 2);
    struct layer* hidden_layer = (pt_net->layers + 1);
    double error = 0.0;

    int i, j;

    for (j = 0; j < lenght; j++) {

        for (i = 0; i < outPutLayer->size; i++) {
            double delta = target[i] - outPutLayer->neurons[i].z;
            error += delta * delta;
        }

        error /= outPutLayer->size - 1;
        error = sqrt(error);
        double delta = 0.0;

        for (i = 0; i < outPutLayer->size; i++) {
            delta = target[i] - outPutLayer->neurons[i].outPut;
            outPutLayer->neurons[i].gradient = delta * (1.0 -
                    outPutLayer->neurons[i].outPut *
                    outPutLayer->neurons[i].outPut);
        }

        for (i = 0; i < hidden_layer->size; i++) {
            double dow = somDOW(hidden_layer, outPutLayer);
            hidden_layer->neurons[i].gradient = dow * (1.0 - hidden_layer->neurons[i].z * hidden_layer->neurons[i].z);
        }


        for (i = 0; i < hidden_layer->size; i++) {
            updateInputWeights(hidden_layer, firstLayer);
        }

    }

}

static
double updateInputWeights(struct layer * hidden_layer, struct layer * prev_layer) {
    double eta = 0.15;
    double alpha = 0.5;

    int i;
    for (i = 0; i < prev_layer->size; i++) {
        struct neuron* currentNeuron = (prev_layer->neurons + i);

        double oldWeight = currentNeuron->deltaWeight;

        double newDelta = eta * currentNeuron->z * currentNeuron->gradient + alpha * oldWeight;

        currentNeuron->deltaWeight = newDelta;
        currentNeuron->weight += newDelta;

    }


}

static
double somDOW(struct layer * hidden_layer, struct layer * next_layer) {

    int i, size = next_layer->size;
    double sumDOW = 0.0;

    for (i = 0; i < size; i++) {
        sumDOW += hidden_layer->neurons[i].weight * next_layer->neurons[i].z;
    }

    return sumDOW;
}