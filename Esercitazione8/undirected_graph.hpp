#pragma once
#include <iostream>
#include <algorithm> 
#include <set>
#include <vector>
#include <map>
#include "undirected_edge.hpp"
#include <cassert>

template <typename T>
class undirected_graph {   
    std::map<T, std::set<T>> lista_adiacenza; // Rappresentazione del grafo tramite lista di adiacenza: mappa che associa a ogni nodo un set di vicini

    std::set<undirected_edge<T>> archi_set; // set per memorizzare gli archi del grafo--> per evitare duplicati 
    std::vector<undirected_edge<T>> archi_vector; // Vettore per memorizzare gli archi del grafo--> per edge_number() e edge_at()

public:
    // Costruttore di default
    undirected_graph() {}

    // Costruttore di copia
    undirected_graph(const undirected_graph& other) : lista_adiacenza(other.lista_adiacenza), archi_set(other.archi_set), archi_vector(other.archi_vector) {} 

    // Metodo neighbours() che restituisce i vicini di un nodo
    std::set<T> neighbours(const T& nodo) const {
        auto itor = lista_adiacenza.find(nodo); // cerchiamo se il nodo esiste nella lista
        if (itor != lista_adiacenza.end()) { // se il nodo esiste, restituiamo i suoi vicini
            return itor->second; // Restituisce i vicini del nodo perchè ogni elemento della lista è una coppia (nodo, vicini) 
        }
        return std::set<T>(); // Restituisce un set vuoto se il nodo non esiste o non ha vicini
    }   

    // Metodo add_edge() che aggiunge un arco al grafo
   void add_edge(T u, T v) {
        undirected_edge<T> nuovo_arco(u, v); // Crea un nuovo arco con i nodi u e v. undirected_edge garantisce che u < v
        if (archi_set.find(nuovo_arco) == archi_set.end()) { // Verifica se l'arco non è già presente
            archi_set.insert(nuovo_arco); // Aggiunge l'arco al set degli archi
            archi_vector.push_back(nuovo_arco); // Aggiunge l'arco al vettore degli archi
            lista_adiacenza[u].insert(v); // Aggiunge v come vicino di u
            lista_adiacenza[v].insert(u); // Aggiunge u come vicino di v
        }
   }
   
   // il metodo add_node non serve perchè i nodi vengono creati quando si aggiunge un arco

    // Metodo all_edges() che restituisce tutti gli archi del grafo.
    std::set<undirected_edge<T>> all_edges() const { // const vuol dire che il metodo non modifica lo stato dell'oggetto
        return archi_set; // Restituisce il set degli archi
    }

    // Metodo all_nodes() che restituisce tutti i nodi del grafo. 
    std::set<T> all_nodes() const {
        std::set<T> nodi; // Set per memorizzare i nodi
        for (const auto& pair : lista_adiacenza) { // range-based for loop per iterare su tutti gli elementi della lista. 
            nodi.insert(pair.first); // ci interessa solo la chiave (first), cioè il nodo
        }
        return nodi; // Restituisce il set dei nodi
    }

    // Metodo edge_number() che restituisce la numerazione di un arco
    int edge_number (const undirected_edge<T>& edge) const {
        int n = archi_vector.size(); // Ottiene il numero totale di archi nel grafo
        for (int i = 0 ; i < n; i++) {
            if (archi_vector[i] == edge) {
                return i; // Restituisce l'indice dell'arco se è presente nel grafo
            }
        }
        return -1; // Restituisce -1 se l'arco non è presente nel grafo
    }   
    // Metodo edge_at() che restituisce l'arco corrispondente a un numero
    undirected_edge<T> edge_at(int i) const {
        int n = archi_vector.size() ; // Ottiene il numero totale di archi nel grafo
        assert ( i >=0 && i < n); // Verifica che l'indice sia valido, se l'assert fallisce, il programma termina con un messaggio di errore
        return archi_vector[i]; // Restituisce l'arco corrispondente all'indice i se è presente nel grafo   
    }


    // Operatore operator-() che calcola la differenza tra due grafi
    undirected_graph operator-(const undirected_graph& other) const {
        undirected_graph grafo_risultato; // Crea un nuovo grafo per memorizzare il risultato della differenza
        for (const auto& arco : archi_set) { // Itera su tutti gli archi del grafo corrente
            if (other.archi_set.find(arco) == other.archi_set.end()) { // Verifica se l'arco non è presente nel grafo other
                grafo_risultato.add_edge(arco.from(), arco.to()); // Aggiunge l'arco al grafo risultato se non è presente in other
            }
        }
        return grafo_risultato; // Restituisce il grafo risultato della differenza
    }
};