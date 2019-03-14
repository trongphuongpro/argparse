# Argument parser for C++

**Constructor**:

  **ArgumentParser**(int argc, char** argv, string descriptor)
  
**Functions**:
- *void* **add_argument**(string positionalArgument, string helpMessage)
- *void* **add_argument**(string shortOptionalArgument, string longOptionalArgument, string defaultValue, string helpMessage)
- *void* **parse_args**()
- *const string&* **get**(const string key)
- *T* **get**<T>(const string key)
