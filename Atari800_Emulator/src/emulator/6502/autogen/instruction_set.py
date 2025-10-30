from jinja2 import Template
import yaml
from pathlib import Path

if __name__ == "__main__":

    base = Path(__file__).parent
    path = f"{base}/instructions.yaml"

    with open(path, "r") as f:
        data = yaml.safe_load(f)
        instructions = data["instruction_set"]

    template_str = """

    #pragma once 

    #include<array>
    #include<cstdint>
    #include<functional>
    #include<iostream>
    #include<optional>
    #include<string>
    #include <unordered_map>

    // Instruction Set

    struct Instruction {
        std::string m_name;
        uint8_t m_opcode;
        size_t m_cycles;
        std::function<void()> m_handler;

        // Constructor
        Instruction()=delete;
        Instruction(std::string name, uint8_t opcode, size_t cycles, std::function<void()> handler)
            : m_name(std::move(name)), m_opcode(opcode), m_cycles(cycles), m_handler(std::move(handler)) {}
    };

    


    std::array<std::optional<Instruction>, 256> dispatch_table = [] {
        std::array<std::optional<Instruction>, 256> table = {};

        {% for instr in instructions -%}
        table[{{ instr.opcode }}] = Instruction("{{instr.mnemonic}}", {{instr.opcode}}, {{instr.cycles}}, handler_lookup["{{instr.handler}}"]);
        {% endfor %}
        return table;
    }();

    """
    
    # {% for instr in instructions -%}
    #  void {{instr.handler}}(){};
    # {% endfor %}
    
    # std::unordered_map<std::string, std::function<void()>> handler_lookup = {
    # {% for instr in instructions -%}
    #     {"{{instr.handler}}", {{instr.handler}}},
    # {% endfor %}
    # };

    template = Template(template_str)
    rendered_code = template.render(instructions=instructions)
    print(rendered_code)

    outPath = f"{base}/instr_dispatch_table.cpp"

    with open(outPath, "w") as f:
        f.write(rendered_code)