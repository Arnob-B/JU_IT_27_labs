import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

class Sample {
  private int id = 101;
  public String name = "Reflection Sample";

  public Sample() {
  }

  public void showMessage() {
    System.out.println("Hello from Sample class!");
  }

  private void secretMethod() {
    System.out.println("This is a private method.");
  }
}

public class Sol4 {
  public static void main(String[] args) {
    try {
      // 1. getClass()
      Sample sampleObj = new Sample();
      Class<?> clazz = sampleObj.getClass();
      System.out.println("Class Name: " + clazz.getName());

      // 2. getMethods() - public methods (including inherited ones)
      System.out.println("\nPublic Methods:");
      Method[] methods = clazz.getMethods();
      for (Method method : methods) {
        System.out.println(method.getName());
      }

      // 3. getDeclaredMethods() - declared in class (including private)
      System.out.println("\nDeclared Methods:");
      Method[] declaredMethods = clazz.getDeclaredMethods();
      for (Method method : declaredMethods) {
        System.out.println(method.getName());
      }

      // 4. getConstructors()
      System.out.println("\nConstructors:");
      Constructor<?>[] constructors = clazz.getConstructors();
      for (Constructor<?> constructor : constructors) {
        System.out.println(constructor);
      }

      // 5. getDeclaredFields()
      System.out.println("\nDeclared Fields:");
      Field[] fields = clazz.getDeclaredFields();
      for (Field field : fields) {
        System.out.println(field.getName());
      }

      // 6. Access private field using setAccessible()
      Field privateField = clazz.getDeclaredField("id");
      privateField.setAccessible(true); // bypass private access
      int idValue = (int) privateField.get(sampleObj);
      System.out.println("\nPrivate Field 'id' value: " + idValue);

      // 7. Access private method using setAccessible()
      Method privateMethod = clazz.getDeclaredMethod("secretMethod");
      privateMethod.setAccessible(true);
      System.out.println("\nInvoking private method:");
      privateMethod.invoke(sampleObj);

    } catch (Exception e) {
      e.printStackTrace();
    }
  }
}
