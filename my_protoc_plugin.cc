#include <google/protobuf/compiler/code_generator.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/compiler/plugin.h>
#include <google/protobuf/io/printer.h>
#include <string>

using namespace google::protobuf;
using namespace google::protobuf::compiler;
using namespace google::protobuf::io;

class MyCodeGenerator : public google::protobuf::compiler::CodeGenerator {
 public:
  virtual bool Generate(
      const FileDescriptor * file,
      const string & parameter, 
      GeneratorContext * generator_context, 
      string * error) const {
    auto *outstream = generator_context->Open(file->name() + ".txt");
    Printer printer(outstream, '$');
    for (int i = 0; i < file->message_type_count(); ++i) {
      PrintMessage(printer, file->message_type(i));
    }
    return true;
  }

 private:
  void PrintMessage(Printer& printer, const Descriptor* msg) const {
    printer.Print("- $name$\n", "name", msg->name());
    printer.Indent();
    for (int i = 0; i < msg->nested_type_count(); ++i) {
      PrintMessage(printer, msg->nested_type(i));
    }
    printer.Outdent();
  }
};

int main(int argc, char** argv) {
  MyCodeGenerator generator;
  return google::protobuf::compiler::PluginMain(argc, argv, &generator);
}
