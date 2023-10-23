#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " <input_file_path> <output_file_path>" << std::endl;
    return 1;
  }

  const char *filePath = argv[1];
  std::ifstream inputFile(filePath);
  const char *outputFilePath = argv[2];
  std::ofstream outputFile(outputFilePath);

  if (!inputFile.is_open())
  {
    std::cerr << "Error opening the file." << std::endl;
    return 1;
  }

  if (!outputFile.is_open())
  {
    std::cerr << "Error opening the output file." << std::endl;
    return 1;
  }

  std::string line;
  while (std::getline(inputFile, line))
  {

    while (!line.empty() && line.back() == ',')
    {
      line.pop_back();
    }

    for (char &c : line)
    {
      if (c != ',')
      {
        int charToInt = c - '0';
        if (charToInt < 10)
        {

          outputFile << "0";
        }
        std::cout << charToInt << std::endl;
      }

      outputFile << c;
    }
    outputFile << std::endl;
  }

  inputFile.close();
  outputFile.close();

  return 0;
}