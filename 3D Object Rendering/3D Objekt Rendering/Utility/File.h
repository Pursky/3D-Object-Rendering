#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "Vertex.h"
#include <string>

using namespace std;

/// <summary>
/// Splits a string at a specific character and returns the substrings as a vector list.
/// </summary>
/// <param name="input">The string that is split.</param>
/// <param name="character">The character where the string splits.</param>
static vector<string> Split(string input, char character)
{
	vector<string> subs;

	int start = 0;

	for (int i = 0; i < input.length(); i++)
	{
		if (input.at(i) == character) {
			subs.push_back(input.substr(start, i - start));
			start = i + 1;
		}
		if (i == input.length() - 1) subs.push_back(input.substr(start, input.length() - 1));
	}

	return subs;
}

/// <summary>
/// Reads vertices, normals, uvs and indices from a file.
/// </summary>
/// <param name="filename">The name of the file.</param>
/// <param name="vertices">The list of vertex structs that the vertices, normals and uvs are added to.</param>
/// <param name="indices">The list of integer that the indices are added to.</param>
static void ReadMesh(string filename, vector<Vertex>* vertices, vector<short>* indices)
{
	vertices->clear();
	indices->clear();

	string line;
	ifstream file("Resources/Meshes/" + filename);

	int index = 0;
	int readState = 0;

	while (getline(file, line))
	{
		if (line._Equal("Vertices:") || line.length() == 0) continue;
		if (line._Equal("Normals:"))
		{
			readState = 1;
			index = 0;
			continue;
		}
		if (line._Equal("UVs:"))
		{
			readState = 2;
			index = 0;
			continue;
		}
		if (line._Equal("Indices:"))
		{
			readState = 3;
			index = 0;
			continue;
		}

		vector<string> subs = Split(line, ' ');

		if (line._Equal("")) continue;

		switch (readState)
		{
		case 0: // Reading Vertices
			vertices->push_back({ stof(subs[0]) , stof(subs[1]), stof(subs[2]) });
			break;
		case 1: // Reading Normals
			vertices->at(index).Normal = { stof(subs[0]) , stof(subs[1]), stof(subs[2]) };
			index++;
			break;
		case 2: // Reading UVs
			vertices->at(index).UV = { stof(subs[0]) , stof(subs[1]) };
			index++;
			break;
		case 3:
			indices->push_back((short)stoi(subs[0]));
			indices->push_back((short)stoi(subs[1]));
			indices->push_back((short)stoi(subs[2]));
			break;
		}
	}

	file.close();
}