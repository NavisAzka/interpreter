#include "../include/main.h"
#include "../include/numConvert.h"

// Kelas untuk Interpreter Sederhana
class SimpleInterpreter
{
private:
    std::map<std::string, std::string> variables;

    std::vector<std::string> split(const std::string &line, char delimiter = ' ')
    {
        std::vector<std::string> result;
        std::stringstream ss(line);
        std::string item;
        while (std::getline(ss, item, delimiter))
        {
            result.push_back(item);
        }
        return result;
    }

    std::string evaluate(const std::string &value)
    {
        if (isdigit(value[0]) || (value[0] == '-' && value.size() > 1))
        {
            return value;
        }
        else if (variables.find(value) != variables.end())
        {
            return variables[value];
        }
        else
        {
            std::cerr << "Unknown variable or value: " << value << std::endl;
            return 0;
        }
    }

public:
    void execute(const std::string &code)
    {
        std::istringstream stream(code);
        std::string line;
        std::vector<std::string> lines;

        while (std::getline(stream, line))
        {
            lines.push_back(line);
        }

        runLines(lines);
    }

private:
    void runLines(const std::vector<std::string> &lines)
    {
        for (size_t i = 0; i < lines.size(); ++i)
        {
            std::string line = lines[i];
            line.erase(0, line.find_first_not_of(" \t"));
            if (line.empty() || line[0] == '#')
                continue;

            std::vector<std::string> parts = split(line);
            std::string command = parts[0];

            if (command == "var")
            {
                if (parts.size() >= 3)
                {
                    std::string varName = parts[1];
                    std::string value = parts[2];
                    variables[varName] = evaluate(value);
                }
            }
            else if (command == "cetak_var")
            {
                if (parts.size() >= 2)
                {
                    std::string value = parts[1];
                    std::cout << evaluate(value) << std::endl;
                }
            }
            else if (command == "cetak")
            {
                if (parts.size() >= 2)
                {
                    // get all string in line
                    std::string value = line.substr(6);
                    std::cout << value << " ";
                }
            }
            else if (command == "cetakln")
            {
                if (parts.size() >= 2)
                {
                    // get all string in line
                    std::string value = line.substr(8);
                    std::cout << value << std::endl;
                }
            }
            else if (command == "ubah_basis")
            {

                if (parts.size() >= 4)
                {
                    std::string num = parts[1];

                    // if num is a variable
                    if (variables.find(num) != variables.end())
                    {
                        num = variables[num];
                    }

                    int basis_awal;
                    if (variables.find(parts[2]) != variables.end())
                    {
                        basis_awal = std::stoi(variables[parts[2]]);
                    }
                    else
                    {
                        basis_awal = std::stoi(parts[2]);
                    }

                    int basis_tujuan;
                    // if basis_tujuan is a variable
                    if (variables.find(parts[3]) != variables.end())
                    {
                        basis_tujuan = std::stoi(variables[parts[3]]);
                    }
                    else
                    {
                        basis_tujuan = std::stoi(parts[3]);
                    }

                    std::string result = convertBase(num, basis_awal, basis_tujuan);
                    std::cout << result << std::endl;
                }
            }
            else if (command == "masukan")
            {
                if (parts.size() >= 2)
                {
                    std::string varName = parts[1];
                    std::string userInput;
                    // std::cout << "Enter value for " << varName << ": ";
                    std::cin >> userInput;
                    variables[varName] = userInput;
                }
            }

            else
            {
                std::cerr << "Unknown command: " << command << std::endl;
            }
        }
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::ifstream inputFile(filename);

    std::string line;
    std::string code;

    while (std::getline(inputFile, line))
    {
        code += line + "\n";
    }

    inputFile.close();

    SimpleInterpreter interpreter;
    interpreter.execute(code);

    return 0;
}
