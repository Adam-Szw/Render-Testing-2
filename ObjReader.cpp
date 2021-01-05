#include "ObjReader.h"
#include "Model.h"
#include "Utilities.h"
#include <fstream>
#include <iostream>

void ObjReader::readVerticesObj(Model* target, std::string objFileLoc)
{
    std::vector<float> positions;
    std::vector<float> textureCoords;
    std::vector<float> normals;

    std::string read = Utilities::getFileContent(objFileLoc);

    int vex = 0;

    for(std::string lineString : Utilities::splitString(&read, 0, '\n'))
    {
        //vertices
        if (lineString.substr(0, 2) == "v ")
        {
            Utilities::addValues(&positions, 2, &lineString);
        }
        //texture coords
        else if (lineString.substr(0, 2) == "vt")
        {
            Utilities::addValues(&textureCoords, 3, &lineString);
        }
        //normals
        else if (lineString.substr(0, 2) == "vn")
        {
            Utilities::addValues(&normals, 3, &lineString);
        }
        //faces
        else if (lineString.substr(0, 2) == "f ")
        {
            //example split: 5/1/1 3/2/1 1/3/1 - > 5/1/1
            std::vector<std::string> triangles = Utilities::splitString(&lineString, 2, ' ');
            target->indexData.push_back(vex + 2); //blender starts indexing with 1 not 0
            target->indexData.push_back(vex + 1);
            target->indexData.push_back(vex);
            vex += 3;
            for (std::string tri : triangles)
            {
                //example split: 5/1/1 - > 5
                std::vector<int> faces = Utilities::splitStringInts(&tri, 0, '/');
                
                int i = faces[0] - 1;
                int j = faces[1] - 1;
                int k = faces[2] - 1;
                Model::Vertex newVer
                {
                    positions[3 * i], positions[3 * i + 1], positions[3 * i + 2],
                    normals[3 * k], normals[3 * k + 1], normals[3 * k + 2],
                    textureCoords[2 * j], textureCoords[2 * j + 1]
                };
                target->vertexData.push_back(newVer);
            }
        }
    }
}
