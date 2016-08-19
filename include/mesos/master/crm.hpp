
class CloudMachine
{
public:
  CloudMachine() {
  }
  std::string az ; //Availability Zone 
  std::string type ; // Machine type

  
  bool operator==(const CloudMachine &other) const
  {
    return az==other.az && type==other.type ;
  }
  
}; //END CloudMachine class
