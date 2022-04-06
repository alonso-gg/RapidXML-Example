#include <iostream>
#include "rapidxml/rapidxml_ext.hpp" //Árbol DOM, Impresión
#include "rapidxml/rapidxml_utils.hpp"
#include <sstream>
#include <fstream>

using namespace std;
using namespace rapidxml; //Namespace de la librería

void extractXMLData(xml_document<>* doc);
void extractNodeData(xml_node<>* node);
