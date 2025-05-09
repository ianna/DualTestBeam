def generate_consumer_class(
    class_name,
    output_location,
    return_type="int",
    return_value="314"
):
    cpp_code = f"""
class {class_name} : public Gaudi::Functional::Consumer<{return_type}()> {{

public:
    {class_name}(const std::string& name, ISvcLocator* svcLoc)
        : Consumer(name, svcLoc,
            KeyValue("OutputLocation", {{ "{output_location}" }})) {{ }}

    {return_type} operator()() const override {{
        return {return_value};
    }}
}};
"""
    return cpp_code


if __name__ == "__main__":
    # Example usage — customize these parameters:
    class_name = "MyProducer"
    output_location = "MyNumber"
    return_type = "int"
    return_value = "314"

    cpp_code = generate_consumer_class(
        class_name,
        output_location,
        return_type,
        return_value
    )

    print(cpp_code)
