namespace binaryStream {
  template<typename T>
  inline std::istream &operator>>(std::istream &is, const binary <T> &x) {
    is.read(const_cast<char *>(reinterpret_cast<const char *>(&x.data)), sizeof(T));
    return is;
  }

  template<typename T>
  inline std::ostream &operator<<(std::ostream &os, const binary <T> &x) {
    os.write(reinterpret_cast<const char *>(&x.data), sizeof(T));
    return os;
  }
}