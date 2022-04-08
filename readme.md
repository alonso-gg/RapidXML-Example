# RapidXML Example 
Este es un ejemplo de uso de la librería RapidXML para C++. La librería permite parsear y manipular la información de cualquier archivo XML (como SVG y HTML). Se adjunta el link para descargar la librería y el manual del creador. 

- [Descargar RapidXML](https://sourceforge.net/projects/rapidxml/files/latest/download) 
- [Manual](http://rapidxml.sourceforge.net/manual.html)  

## Cómo implementar la librería 
La librería se descarga como un archivo zip, una vez descomprimido el archivo tendremos una carpeta con los siguientes archivos: 

- La licencia y el manual de la librería. 
- ```rapidxml.hpp```: Es el archivo principal con las clases para la manipulación del XML. 
- ```rapidxml_print.hpp```: Incluye métodos para imprimir el XML como texto y para convertir a string. 
- ```rapidxml_iterators.hpp```: Iteradores para el manejo de memoria y el desplazamiento por el XML. 
- ```rapidxml_utils.hpp```: Incluye una clase para leer el archivo y métodos para contar atributos y elementos. 

Sin embargo, la librería tiene un bug donde varios métodos en el archivo rapidxml\_print.hpp no están definidos. Puede ver este problema y su solución en StackOverflow: [Problema con el print header](https://stackoverflow.com/questions/14113923/rapidxml-print-header-has-undefined-methods). 

En resumen, debemos agregar el archivo ```rapidxml_ext.hpp``` en la carpeta de la librería. Este archivo aparte de solucionar el bug, es el que incluiremos en nuestro código junto al ```namespace```. Además, podemos incluir ```rapidxml_utils.hpp``` para leer el archivo XML fácilmente. Así que en el preprocesador de nuestro código debemos tener lo siguiente: 
```c++

#include "rapidxml/rapidxml_ext.hpp"
#include "rapidxml/rapidxml_utils.hpp"
using namespace rapidxml;

```
## Leer y parsear XML 
Para leer el archivo XML usamos un objeto ```file``` que recibe la ubicación del archivo XML a leer. Por otro lado, para parsear y manipular la información necesitamos un objeto ```xml_document```. Con el método ```xml_document::parse()``` enviamos la información del archivo al objeto para parsearla.
```c++

file<> theFile("whatever.xml");
xml_document<> myDoc;
myDoc.parse<0>(theFile.data());

```
Ahora toda la información está en un árbol DOM cuya raíz es el objeto ```xml_document```. 
## Recorrer la información 
Recorrer la información se traduce en recorrer un árbol donde cada nodo representa cada elemento del XML. Los elementos del XML se representan como nodos declarados como objetos ```xml_node```. Para obtener el *primer elemento* del XML es tan simple como: 
```c++

xml_node<>* firstNode = myDoc->first_node();

```
Ahora ```firstNode``` apunta al primer elemento del XML. Para cada elemento podemos acceder a su nombre y valor, además nos podemos mover al siguiente elemento *en el mismo nivel*. 
```c++

string theName = firstNode->name();
string theValue = firstNode->value();
xml_node<>* secondNode = firstNode->next_sibling();

```
Para acceder a los atributos de un elemento primero debemos acceder al primero de ellos y luego desplazarnos por una lista, para esto usamos un objeto ```xml_attribute```. 
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
En caso de que se haya llegado al final de una lista de nodos o de atributos, los métodos ```xml_node::next_sibling()``` y ```xml_attribute::next_attribute()``` retornan ```NULL```.
## Buscar un elemento o atributo 
Si queremos buscar un elemento o atributo específico, basta con escribir su nombre en el paréntesis cuando nos movemos por el árbol DOM. 
```c++

xml_node<>* theDog = myDoc->first_node("dog"); //Primer elemento 'dog' en el XML
xml_attribute<>* theAttrib = firstNode->first_attribute()

``` 

