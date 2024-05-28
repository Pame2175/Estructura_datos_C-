#include <iostream>
#include <list>
#include <queue> 
#define INFINITO 10000000
using namespace std;
class Grafo{
    private:
        int V; //número de vértices
        
        list<pair<int, int>> *adyacente; //puntero para un array que contiene las listas de adyacencia
    public:
        //constructor
        Grafo(int V){
            this->V=V;
            
            /*
            creación de las listas donde cada lista es una lista de pairs
            donde cada pair es formado por el vértice destino y el costo
            */
            adyacente= new list<pair<int,int>>[V];
        }
        
        //agregar una arista al grafo de v1 a v2
        
        void agregarArista(int v1, int v2, int costo){
            adyacente[v1].push_back(make_pair(v2, costo));
        }
        
        //algoritmo de Dijkstra
        
        int dijkstra(int origen, int destino){
            //vector de distancias
            int distancia[V];
            /*vecto de visitados sirve para el caso de que el vértice
            ya haya sido expandido(visitado), y no volverlo a hacer
            */
            int visitados[V];
            
            priority_queue <pair<int, int>,
                            vector<pair<int,int>>, greater<pair<int, int>>> pq;
                            
            //inicializar el vector de distancias y visitados
            for (int i=0;i<V;i++){
                distancia[i]=INFINITO;
                visitados[i]=false;
            }
            //la distancia de origen para origen es 0 
            distancia[origen]=0;
            //inserta en la fila
            pq.push(make_pair(distancia[origen], origen));
            
            while(!pq.empty()){
                pair<int,int>primero=pq.top(); //extrae un pair del tope
                int ultimo=primero.second; //obtiene un vértice del par
                pq.pop(); //elimina la cola
                
                //verifica si un vértice no fue visitado
                if(visitados[ultimo]==false){
                    //marca como visitado
                    visitados[ultimo]=true;
                    
                list<pair<int, int> >::iterator it;
                    
                    //atraviesa los vértices "v" adyacentes de "ultimo"
                    for(it=adyacente[ultimo].begin(); it!=adyacente[ultimo].end(); it++){
                        //obtener el vertice adyacente y el costo de la arista
                        int v=it->first;
                        int costo_arista=it->second;
                        
                        if(distancia[v]>(distancia[ultimo]+ costo_arista)){
                            //actualiza la distancia de "v" e inserta en la cola
                            distancia[v]=distancia[ultimo]+costo_arista;
                            pq.push(make_pair(distancia[v],v));
                        }
                    }
                }
            }
            //retorna distancia mínima
            return distancia[destino];
        
        }
};
int main(int argc, char *argv[]){
    
    Grafo grafo(5);
    grafo.agregarArista(0,1,4);
    grafo.agregarArista(0,2,2);
    grafo.agregarArista(0,3,5);
    grafo.agregarArista(1,4,1);
    grafo.agregarArista(2,1,1);
    grafo.agregarArista(2,3,2);
    grafo.agregarArista(2,4,1);
    grafo.agregarArista(3,4,1);
    
    cout<< grafo.dijkstra(0,4)<<endl;
    
    return 0;
}
