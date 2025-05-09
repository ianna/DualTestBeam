def generate_transform_algorithm_class(
    class_name,
    input1_loc,
    input2_loc,
    output_loc,
    output_data_type="OutputData",
    input1_type="Input1",
    input2_type="Input2"
):
    cpp_code = f"""
class {class_name} : public TransformAlgorithm<{output_data_type}(const {input1_type}&, const {input2_type}&)> {{

public:
    {class_name}(const std::string& name, ISvcLocator* pSvc)
        : TransformAlgorithm(
              name,
              pSvc, {{
                  KeyValue("Input1Loc", "{input1_loc}"),
                  KeyValue("Input2Loc", "{input2_loc}") }},
              KeyValue("OutputLoc", "{output_loc}")) {{ }}

    {output_data_type} operator()(const {input1_type}& in1, const {input2_type}& in2) const override {{
        return in1 + in2;
    }}
}};
"""
    return cpp_code


if __name__ == "__main__":
    # Example usage — you can customize these parameters:
    class_name = "MySum"
    input1_loc = "Data1"
    input2_loc = "Data2"
    output_loc = "Output/Data"

    cpp_code = generate_transform_algorithm_class(
        class_name,
        input1_loc,
        input2_loc,
        output_loc
    )

    print(cpp_code)
