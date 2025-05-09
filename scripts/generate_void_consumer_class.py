def generate_void_consumer_class(
    class_name,
    input_location,
    input_type="int",
    print_message='Printing input'
):
    cpp_code = f"""
class {class_name} : public Gaudi::Functional::Consumer<void(const {input_type}&)> {{

public:
    {class_name}(const std::string& name, ISvcLocator* svcLoc)
        : Consumer(name, svcLoc,
            KeyValue("InputLocation", {{ "{input_location}" }})) {{ }}

    void operator()(const {input_type}& input) const override {{
        info << "{print_message}: " << input << endmsg;
    }}
}};
"""
    return cpp_code


if __name__ == "__main__":
    # Example usage — customize these parameters:
    class_name = "MyConsumer"
    input_location = "MyNumber"
    input_type = "int"
    print_message = "Printing input"

    cpp_code = generate_void_consumer_class(
        class_name,
        input_location,
        input_type,
        print_message
    )

    print(cpp_code)
