package acorn.classloader;
import java.util.Map;

public class ByteArrayClassLoader extends ClassLoader {

    private final Map<String, byte[]> classBytes;

    public ByteArrayClassLoader(Map<String, byte[]> classBytes) {
        this.classBytes = classBytes;
    }
    public Class<?> defineClass(String name, byte[] bytecode) {
        return defineClass(name, bytecode, 0, bytecode.length);
    }

    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        byte[] bytes = classBytes.get(name);
        if (bytes == null) {
            throw new ClassNotFoundException(name);
        }
        return defineClass(name, bytes, 0, bytes.length);
    }
}