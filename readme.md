# RapidXML Example 
Este es un ejemplo de uso de la librería RapidXML para C++. La librería permite parsear y manipular la información de cualquier archivo XML (como SVG y HTML). Se adjunta el link para descargar la librería y el manual del creador. 

- [Descargar RapidXML](https://sourceforge.net/projects/rapidxml/files/latest/download) 
- [Manual](http://rapidxml.sourceforge.net/manual.html)  

### Contenidos
1. [ Cómo implementar la librería. ](#implementarLibreria)
2. [ Leer y parsear XML. ](#leerParsearXML)
3. [ Recorrer la información. ](#recorrerInfo)
4. [ Buscar un elemento o atributo . ](#buscarElemento)
5. [ Agregar nuevos elementos. ](#agregarElementos)
6. [ Escribir un archivo XML. ](#escribirXMl)

<a name="implementarLibreria"></a> 

## Cómo implementar la librería

La librería se descarga como un archivo zip, una vez descomprimido el archivo tendremos una carpeta con los siguientes archivos: 

- La licencia y el manual de la librería. 
- `rapidxml.hpp`: Es el archivo principal con las clases para la manipulación del XML. 
- `rapidxml_print.hpp`: Incluye métodos para imprimir el XML como texto y para convertir a string. 
- `rapidxml_iterators.hpp`: Iteradores para el manejo de memoria y el desplazamiento por el XML. 
- `rapidxml_utils.hpp`: Incluye una clase para leer el archivo y métodos para contar atributos y elementos. 

Sin embargo, la librería tiene un bug donde varios métodos en el archivo rapidxml\_print.hpp no están definidos. Puede ver este problema y su solución en StackOverflow: [Problema con el print header](https://stackoverflow.com/questions/14113923/rapidxml-print-header-has-undefined-methods). 

En resumen, debemos agregar el archivo `rapidxml_ext.hpp` en la carpeta de la librería. Este archivo aparte de solucionar el bug, es el que incluiremos en nuestro código junto al `namespace`. Además, podemos incluir `rapidxml_utils.hpp` para leer el archivo XML fácilmente. Así que en el preprocesador de nuestro código debemos tener lo siguiente: 
```c++

#include "rapidxml/rapidxml_ext.hpp"
#include "rapidxml/rapidxml_utils.hpp"
using namespace rapidxml;

``` 
<a name="leerParsearXML"></a>

## Leer y parsear XML 
Para leer el archivo XML usamos un objeto `file` que recibe la ubicación del archivo XML a leer. Por otro lado, para parsear y manipular la información necesitamos un objeto `xml_document`. Con el método `xml_document::parse()` enviamos la información del archivo al objeto para parsearla.
```c++

file<> theFile("whatever.xml");
xml_document<> myDoc;
myDoc.parse<0>(theFile.data());

```
Ahora toda la información está en un árbol DOM cuya raíz es el objeto `xml_document`. 
<a name="recorrerInfo"></a>

## Recorrer la información 
Recorrer la información se traduce en recorrer un árbol donde cada nodo representa cada elemento del XML. Los elementos del XML se representan como nodos declarados como objetos `xml_node`. Para obtener el _primer elemento_*_ del XML es tan simple como: 
```c++

xml_node<>* firstNode = myDoc->first_node();

```
Ahora `firstNode` apunta al primer elemento del XML. Para cada elemento podemos acceder a su nombre y valor, además nos podemos mover al siguiente elemento _en el mismo nivel_. 
```c++

string theName = firstNode->name();
string theValue = firstNode->value();
xml_node<>* secondNode = firstNode->next_sibling();

```
Para acceder a los atributos de un elemento primero debemos acceder al primero de ellos y luego desplazarnos por una lista, para esto usamos un objeto `xml_attribute`. 
```c++

xml_attribute<>* theAttrib = firstNode->first_attribute() //theAttrib apunta al primer atributo del elemento
xml_attribute<>* theNextAttrib = theAttrib->next_attribute() //theNextAttrib apunta al segundo atributo del elemento

``` 
Al igual que con los elementos, podemos acceder al nombre y valor de cada atributo. 
```c++

string theAttribName = theAttrib->name();
string theAttribValue = theAttrib->value();

``` 
Por último, podríamos encontrar elementos dentro de elementos. Similar a la forma de acceder a los atributos, primero accedemos al primer sub-elemento y luego los seguimos recorriendo. 
```c++

xml_node<>* subNode1 = firstNode->first_node();
xml_node<>* subNode2 = subNode1->next_sibling();

``` 
En caso de que se haya llegado al final de una lista de nodos o de atributos, los métodos `xml_node::next_sibling()` y `xml_attribute::next_attribute()` retornan `NULL`. 
<a name="buscarElemento"></a>

## Buscar un elemento o atributo 
Si queremos buscar un elemento o atributo específico, basta con escribir su nombre en el paréntesis cuando nos movemos por el árbol DOM. 
```c++

xml_node<>* theDog = myDoc->first_node("dog"); //Primer elemento 'dog' en el XML
xml_attribute<>* theAge = theDog->first_attribute("age") //Atributo 'age' del elemento 'dog'

xml_node<>* theCat = theDog->next_sibling("cat"); //Primer elemento 'cat' que esté después del elemento 'dog'

``` 
<a name="agregarElementos"></a>

## Agregar nuevos elementos 
Para agregar información a nuestro XML debemos usar métodos `allocate` para enlazar los nuevos strings con el árbol DOM. En caso de agregar un elemento, debemos indicar que es un  `node_element` y su nombre. Luego de esto podemos agregarle atributos y un valor. Para los atributos debemos indicar el nombre del atributo y su valor.
```c++

xml_node<> *newNode = myDoc.allocate_node(node_element, "donkey");
newNode->value("Bruno")
myDoc.first_node()->append_node(newNode);

xml_attribute<> *newAttr = myDoc.allocate_attribute("age", "5");
newNode->append_attribute(newAttr);

``` 
El código anterior produciría las siguientes líneas en XML: 
```XML

<donkey age="5">
    Bruno
<donkey/>

``` 
<a name="escribirXMl"></a>

## Escribir un archivo XML 
Debemos tener el árbol DOM con toda la información que queremos escribir en el XML. 
```c++

//Importante tener ambas directrices
#include <fstream>
using namespace std;

//...//

ofstream theNewFile("another.xml"); //Crea el archivo en la ubicación indicada

stringstream ss;
ss << *myDoc.first_node(); //Convierte el árbol DOM en un stringstream
string stringXML = ss.str(); //Convierte de stringstream a string

theNewFile << stringXML; //Escribe el string en el archivo
theNewFile.close();

``` 
Ya tendremos un nuevo archivo XML con todo el teje y maneje de los datos.  

***
###### ITCR Campus Central Cartago
###### Análisis de algoritmos
###### Caso 3 - Assigment
###### Hecho por: Alonso Garita Granados

