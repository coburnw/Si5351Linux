# Si5351Linux
Linux interface to the Etherkit Si5351Arduino Library

Altho this wrapper is somewhat functional, its intent is to explore
extending the Etherkit Si5351 Arduino library to other platforms using git submodules
and brucemack's interface abstraction (https://github.com/brucemack/Si5351Arduino).

### What is here ###
currently there are two branches, master and poly.  
  * The master branch uses a minimal version of Bruce's interface, as intended, using 
a SI5351_ARDUINO preprocessor define to switch between arduino and non-arduino platforms.  
  * The poly branch expands on Bruce's work with a fully polymorphic c++ interface that 
removes the need for the SI5351_ARDUINO define.  This allows the etherkit library to be dropped
into a repository such as this one as a submodule, without modification.

### Notes ###
  * Some info on using [submodules in projects](https://github.blog/2016-02-01-working-with-submodules/)
including first time clone to populate the submodules. 
  * A good SO post on [detached heads](https://stackoverflow.com/a/20797186).
