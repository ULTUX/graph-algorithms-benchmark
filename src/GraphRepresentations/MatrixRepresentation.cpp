//
// Created by Wladyslaw Nowak on 17.05.2021.
//

#include <stdexcept>
#include <iostream>
#include "MatrixRepresentation.h"

MatrixRepresentation::MatrixRepresentation(int vertSize, int edgeSize, int startVert, int endVert, bool isDirected)
        : vertSize(vertSize),
          edgeSize(edgeSize),
          startVert(startVert),
          endVert(endVert),
          isDirected(isDirected) {
    adjMatrix = new int *[vertSize];
    for (int i = 0; i < vertSize; i++) {
        adjMatrix[i] = new int[vertSize];
        for (int j = 0; j < vertSize; j++){
            adjMatrix[i][j] = 0;
        }
    }

}

void MatrixRepresentation::addConnection(int begin, int end, int weight) {
    if (isDirected) {
        if (begin < 0 || begin > vertSize || end < 0 || end > vertSize)
            throw std::invalid_argument("Invalid vertices were passed.");
        if ((adjMatrix[begin][end] == 0 && weight != 0 && currEdgeSize + 1 > edgeSize))
            throw std::logic_error("Graph is already completed, you can't add any more edges to this graph.");
        if (adjMatrix[begin][end] == 0 && weight != 0) {
            currEdgeSize++;
        }
        if (adjMatrix[begin][end] != 0 && weight == 0) currEdgeSize--;
        adjMatrix[begin][end] = weight;
    } else {
        if (begin < 0 || begin > vertSize || end < 0 || end > vertSize)
            throw std::invalid_argument("Invalid vertices were passed.");
        if (adjMatrix[begin][end] == 0 && weight != 0 && currEdgeSize + 1 > edgeSize)
            throw std::logic_error("Graph is already completed, you can't add any more edges to this graph.");
        if (adjMatrix[begin][end] == 0 && weight != 0) {
            currEdgeSize++;
        }
        if (adjMatrix[begin][end] != 0 && weight == 0) currEdgeSize--;
        adjMatrix[begin][end] = weight;
        adjMatrix[end][begin] = weight;
    }
}

int **MatrixRepresentation::getAdjMatrix() {
    if (currEdgeSize < edgeSize) throw std::logic_error("Graph was not fully created, waiting for more edges.");
    return this->adjMatrix;
}

void MatrixRepresentation::print() {
    std::cout<<std::endl;
    std::cout<<std::endl;
    for (int i = 0; i < vertSize; i++){
        for (int j = 0; j < vertSize; j++){
            std::cout<<adjMatrix[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;

}

void MatrixRepresentation::setEdgeSize(int n) {
    this->currEdgeSize = 0;
    this->edgeSize = n;
}

void MatrixRepresentation::setVertSize(int n) {
    for (int i = 0; i < vertSize; i++) {
        delete[] this->adjMatrix[i];
    }
    delete[] this->adjMatrix;
    this->vertSize = n;
    adjMatrix = new int *[vertSize];
    for (int i = 0; i < vertSize; i++) {
        adjMatrix[i] = new int[vertSize];
        for (int j = 0; j < vertSize; j++){
            adjMatrix[i][j] = 0;
        }
    }
}

void MatrixRepresentation::setEndingVertex(int v) {
    this->endVert = v;
}

void MatrixRepresentation::setStartingVertex(int v) {
    this->startVert = v;
}

void MatrixRepresentation::clone(MatrixRepresentation* representation) {
    setVertSize(representation->vertSize);
    setEdgeSize(representation->edgeSize);
    startVert = representation->startVert;
    endVert = representation->endVert;
    if (isDirected)
        for (int i = 0; i < representation->vertSize; i++) {
            for (int j = 0; j < representation->vertSize; j++){
                if (representation->adjMatrix[i][j] != 0){
                    addConnection(i, j, representation->adjMatrix[i][j]);
                }
            }
        }
    else
        for (int i = 0; i < representation->vertSize; i++) {
            for (int j = 0; j < representation->vertSize; j++){
                if (representation->adjMatrix[j][i] != 0) {
                    addConnection(j, i, representation->adjMatrix[j][i]);
                }
            }
        }
}

bool MatrixRepresentation::hasNegativeWeights() {
    for (int i = 0; i < vertSize;i++){
        for (int j = 0; j < vertSize; j++){
            if (adjMatrix[i][j] < 0) return true;
        }
    }
    return false;
}
