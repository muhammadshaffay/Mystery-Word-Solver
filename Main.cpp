#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string ReadFile();
char** PopulateGrid(string, int&, int&);
string WordList();
char** Populate_wordList(string str, int&, int*);
void searchWord(char** str, int, int, char** words, int, int*);

int main()
{
	string str = ReadFile();
	int str_row, str_cols;
	char** ptr = PopulateGrid(str, str_row, str_cols);

	cout << "\n \n \n";

	string word = WordList();
	int word_row;
	int word_cols[30];
	
	char** p = Populate_wordList(word, word_row, word_cols);

	searchWord(ptr, str_row, str_cols, p, word_row, word_cols);

	return 0;
}

string ReadFile()
{
	ifstream myfile;
	myfile.open("grid.txt");
	string str;
	string temp;

	if (!myfile)
	{
		cout << "Grid.txt file not found" << endl;
	}
	else if (myfile)
	{
		while (getline(myfile, temp))
		{
			str += temp;
			if (str.length() != 0)
			{
				str += ' ';
			}
		}
		myfile.close();
	}
	return str;
}

char** PopulateGrid(string str, int& str_row, int& str_cols)
{
	int row = 0;
	int cols = 0;

	for (int i = 0; str[i] != ' '; i++)
	{
		cols += 1;
	}

	int i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			row += 1;
		}
		else if (str[i + 1] == '\0')
		{
			row += 1;
		}
		i++;
	}

	char** ptr = new char* [row];

	for (int i = 0; i < row; i++)
	{
		ptr[i] = new char[cols];
	}

	int r = 0;
	int c = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			r += 1;
			c = 0;
		}
		else if (str[i] != ' ')
		{
			ptr[r][c] = str[i];
			c += 1;
		}
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << ptr[i][j] << " ";
		}
		cout << endl;
	}
	str_row = row;
	str_cols = cols;
	return ptr;
}

string WordList()
{
	ifstream myfile;
	myfile.open("wordList.txt");
	string str;
	string temp;

	if (!myfile)
	{
		cout << "wordList.txt file not found" << endl;
	}
	else if (myfile)
	{
		while (getline(myfile, temp))
		{
			str += temp;
			if (str.length() != 0)
			{
				str += ' ';
			}
		}
		myfile.close();
	}
	return str;
}

char** Populate_wordList(string str, int& word_row, int* word_cols)
{
	int row = 0;

	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			row += 1;
		}
		else if (str[i + 1] == '\0')
		{
			row += 1;
		}
		i++;
	}
	word_row = row;
	
	int counter = 0;
	int indexer = 0;
	
	for (int i = 0; str[i] != '\0'; i++)
		{
			if (str[i] == ' ')
			{
				word_cols[indexer] = counter;
				counter = 0;
				indexer += 1;
			}
			else
				counter += 1;
		}

	char** ptr = new char* [row];

	for (int i = 0; i < row; i++)
	{
		ptr[i] = new char[word_cols[i]];
	}
	
	int r = 0;
	int c = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			r += 1;
			c = 0;
		}
		else if (str[i] != ' ')
		{
			ptr[r][c] = str[i];
			c += 1;
		}
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < word_cols[i]; j++)
		{
			cout << ptr[i][j] << " ";
		}
		cout << endl;
	}

	return ptr;
}


void searchWord(char** ptr, int str_row, int str_cols, char** p, int word_row, int* word_cols)
{
	fstream my_file("Output.txt");
	my_file.open("Output.txt", ios::app);
	cout << my_file << endl;
	cout << "\n \n";
	for (int i = 0; i < word_row; i++)
	{
		for (int j = 0; j < word_cols[i]; j++)
		{
			for (int x = 0; x < str_row; x++)
			{
				for (int y = 0; y < str_cols; y++)
				{
					if (ptr[x][y] == p[i][j])
					{
						if (x - 1 >= 0)// North
						{
							if (ptr[x - 1][y] == p[i][j + 1])
							{
								int counter_1 = 0;
								for (int z = 0; z < word_cols[i]; z++)
								{
									if (x - z >= 0)
									{
										if (ptr[x - z][y] == p[i][z])
										{
											counter_1 += 1;
										}
										if (counter_1 == word_cols[i])
										{
											for (int r = 0; r < word_cols[i]; r++)
											{
												my_file << p[i][r];
											}
											my_file << " | ";

											my_file << "(Starting Index) : " << x << " , " << y << " | ";
											my_file << "(Ending Index) : " << x - z << " , " << y  << " | ";
											my_file << "Directions : North  \n" << endl;
											counter_1 = 0;
											break;
										}
									}
								}
							}
						}

						if (y + 1 < str_cols && x - 1 >= 0)// North - East
						{
							if (ptr[x - 1][y + 1] == p[i][j + 1])
							{
								int counter_2 = 0;
								for (int z = 0; z < word_cols[i]; z++)
								{
									if (y + z < str_cols && x - z >= 0)
									{
										if (ptr[x - z][y + z] == p[i][z])
										{
											counter_2 += 1;
										}
										if (counter_2 == word_cols[i])
										{
											for (int r = 0; r < word_cols[i]; r++)
											{
												my_file << p[i][r];
											}
											my_file << " | ";

											my_file << "(Starting Index) : " << x << " , " << y << " | ";
											my_file << "(Ending Index) : " << x - z<< " , " << y + z << " | ";
											my_file << "Directions : North - East \n" << endl;
											counter_2 = 0;
											break;
										}
									}
								}
							}
						}

						if (ptr[x][y + 1] == p[i][j + 1])// East
						{
							int counter_3 = 0;
							for (int z = 0; z < word_cols[i]; z++)
							{
								if (ptr[x][y + z] == p[i][z])
								{
									counter_3 += 1;
								}
								if (counter_3 == word_cols[i])
								{
									for (int r = 0; r < word_cols[i]; r++)
									{
										my_file << p[i][r];
									}
									my_file << " | ";

									my_file << "(Starting Index) : " << x << " , " << y << " | ";
									my_file << "(Ending Index) : " << x << " , " << y+z << " | ";
									my_file << "Directions : East \n" << endl;
									counter_3 = 0;
									break;
								}
							}
						}

						if (((y + 1) < str_cols) && ((x + 1) < str_row))// South East
						{
							if (ptr[x + 1][y + 1] == p[i][j + 1])
							{
								int counter_4 = 0;
								for (int z = 0; z < word_cols[i]; z++)
								{
									if (((y + z) < str_cols) && ((x + z) < str_row))
									{
										if (ptr[x + z][y + z] == p[i][z])
										{
											counter_4 += 1;
										}
										if (counter_4 == word_cols[i])
										{
											for (int r = 0; r < word_cols[i]; r++)
											{
												my_file << p[i][r];
											}
											my_file << " | ";

											my_file << "(Starting Index) : " << x << " , " << y << " | ";
											my_file << "(Ending Index) : " << x + z << " , " << y + z << " | ";
											my_file << "Directions : South - East \n" << endl;
											counter_4 = 0;
											break;
										}
									}
								}
							}
						}

						if (x + 1 < str_row)// South
						{
							if (ptr[x + 1][y] == p[i][j + 1])
							{
								int counter_5 = 0;
								for (int z = 0; z < word_cols[i]; z++)
								{
									if (x + z < str_row)
									{
										if (ptr[x + z][y] == p[i][z])
										{
											counter_5 += 1;
										}
										if (counter_5 == word_cols[i])
										{
											for (int r = 0; r < word_cols[i]; r++)
											{
												my_file << p[i][r];
											}
											my_file << " | ";

											my_file << "(Starting Index) : " << x << " , " << y << " | ";
											my_file << "(Ending Index) : " << x + z << " , " << y  << " | ";
											my_file << "Directions : South  \n" << endl;
											counter_5 = 0;
											break;
										}
									}
								}
							}
						}

						if (((y - 1) >= 0) && ((x + 1) < str_row)) //south west
						{
							if (ptr[x + 1][y - 1] == p[i][j + 1])
							{
								int counter_6 = 0;
								for (int z = 0; z < word_cols[i]; z++)
								{
									if (((y - z) >= 0) && ((x + z) < str_row))
									{
										if (ptr[x + z][y - z] == p[i][z])
										{
											counter_6 += 1;
										}
										if (counter_6 == word_cols[i])
										{
											for (int r = 0; r < word_cols[i]; r++)
											{
												my_file << p[i][r];
											}
											my_file << " | ";

											my_file << "(Starting Index) : " << x << " , " << y << " | ";
											my_file << "(Ending Index) : " << x + z << " , " << y - z << " | ";
											my_file << "Directions : South - West \n" << endl;
											counter_6 = 0;
											break;
										}
									}
								}
							}
						}

						if (y - 1 >= 0)// west
						{
							if (ptr[x][y - 1] == p[i][j + 1])
							{
								int counter_7 = 0;
								for (int z = 0; z < word_cols[i]; z++)
								{
									if (y - z >= 0)
									{
										if (ptr[x][y - z] == p[i][z])
										{
											counter_7 += 1;
										}
										if (counter_7 == word_cols[i])
										{
											for (int r = 0; r < word_cols[i]; r++)
											{
												my_file << p[i][r];
											}
											my_file << " | ";

											my_file << "(Starting Index) : " << x << " , " << y << " | ";
											my_file << "(Ending Index) : " << x  << " , " << y - z << " | ";
											my_file << "Directions : West \n" << endl;
											counter_7 = 0;
											break;
										}
									}
								}
							}
						}

						if (((y - 1) >= 0) && ((x - 1) >= 0))//north west
						{
							if (ptr[x - 1][y - 1] == p[i][j + 1])
							{
								int counter_8 = 0;
								for (int z = 0; z < word_cols[i]; z++)
								{
									if (((y - z) >= 0) && ((x - z) >= 0))
									{
										if (ptr[x - z][y - z] == p[i][z])
										{
											counter_8 += 1;
										}
										if (counter_8 == word_cols[i])
										{
											for (int r = 0; r < word_cols[i]; r++)
											{
												my_file << p[i][r];
											}
											my_file << " | ";

											my_file << "(Starting Index) : " << x << " , " << y << " | ";
											my_file << "(Ending Index) : " << x - z << " , " << y - z << " | ";
											my_file << "Directions : North - West \n" << endl;
											counter_8 = 0;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	my_file.close();
}
