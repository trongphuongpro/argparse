# Argument parser for C++

**Constructor**:

  **ArgumentParser**(*int* argc, *char*** argv, *const string&* descriptor)
  
**Functions**:
- *void* **add_argument**(*const string&* positionalArgument, *const string&* helpMessage)
- *void* **add_argument**(*const string&* shortOptionalArgument, *const string&* longOptionalArgument, *const string&* defaultValue, *const string&* helpMessage)
- *void* **parse_args**()
- *const string&* **get**(*const string&* key)
- *T* **get**&lt;T&gt;(*const string&* key)
