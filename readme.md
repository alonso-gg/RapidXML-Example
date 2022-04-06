# RapidXML Example 
Este es un ejemplo de uso de la librería RapidXML para C++. La librería permite parsear y manipular la información de cualquier archivo XML (como SVG y HTML). Se adjunta el link para descargar la librería y el manual del creador. 

- [Descargar RapidXML](https://sourceforge.net/projects/rapidxml/files/latest/download) 
- [Manual](http://rapidxml.sourceforge.net/manual.html)  

### Cómo implementar la librería 
La librería se descarga como un archivo zip, una vez descomprimido el archivo tendremos una carpeta con los siguientes archivos: 

- La licencia y el manual de la librería. 
- rapidxml.hpp: Es el archivo principal con las clases para la manipulación del XML. 
- rapidxml\_print.hpp: Incluye métodos para imprimir el XML como texto y para convertir a string. 
- rapidxml\_iterators.hpp: Iteradores para el manejo de memoria y el desplazamiento por el XML. 
- rapidxml\_utils.hpp: Incluye una clase para leer el archivo y métodos para contar atributos y elementos. 

Sin embargo, la librería tiene un bug donde varios métodos en el archivo rapidxml\_print.hpp no están definidos. Puede ver este problema y su solución en StackOverflow: [Problema con el print header](https://stackoverflow.com/questions/14113923/rapidxml-print-header-has-undefined-methods). 

En resumen, debemos agregar el archivo ```rapidxml\_ext.hpp``` en la carpeta de la librería. Este archivo aparte de solucionar el bug, es el que incluiremos en nuestro código. Así que en el preprocesador de nuestro código debemos tener lo siguiente: 
```c++

#include "rapidxml/rapidxml_ext.hpp"
#include "rapidxml/rapidxml_utils.hpp"
using namespace rapidxml;

```

