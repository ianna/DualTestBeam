#include "k4FWCore/Transformer.h"

#include <string>

struct {class_name} final
    : k4FWCore::Transformer<{output_collection}(const {input_collection}&)> {{
  {class_name}(const std::string& name, ISvcLocator* svcLoc)
      : Transformer(name, svcLoc, {{KeyValues("InputCollection", {{"MCParticles"}})}},
                    {{KeyValues("OutputCollection", {{"NewMCParticles"}})}}) {{}}

  {output_collection} operator()(const {input_collection}& input) const override {{
    info() << "Transforming " << input.size() << " particles" << endmsg;
    auto coll_out = {output_collection}();
    for (const auto& particle : input) {{
      auto new_particle = coll_out.create();
      {logic_str}
    }}
    return coll_out;
  }}

private:
  Gaudi::Property<int> m_offset{{this, "Offset", {offset_default}, "Integer to add to the dummy values written to the edm"}};
}};

DECLARE_COMPONENT({class_name})
"""
    return cpp_code


# Example usage
if __name__ == "__main__":
    cpp = generate_transformer_class("MyCustomTransformer")
    with open("MyCustomTransformer.cpp", "w") as f:
        f.write(cpp)
    print("C++ transformer class written to MyCustomTransformer.cpp")
