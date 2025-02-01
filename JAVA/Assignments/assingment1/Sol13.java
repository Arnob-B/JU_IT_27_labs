class Automobile {
  private String make, type;
  private float maxSpeed, price, mileage;
  private int registrationNumber;

  Automobile() {
  }

  public String getMake() {
    return make;
  }

  public String getType() {
    return type;
  }

  public float getPrice() {
    return price;
  }

  public float getMileage() {
    return mileage;
  }

  public float getMaxSpeed() {
    return maxSpeed;
  }

  public int getRegistrationNumber() {
    return registrationNumber;
  }

  public Automobile setMake(String make) {
    this.make = make;
    return this;
  }

  public Automobile setType(String type) {
    this.type = type;
    return this;
  }

  public Automobile setPrice(float price) {
    this.price = price;
    return this;
  }

  public Automobile setMileage(float mileage) {
    this.mileage = mileage;
    return this;
  }

  public Automobile setMaxSpeed(float maxSpeed) {
    this.maxSpeed = maxSpeed;
    return this;
  }

  public Automobile setRegistrationNumber(int registrationNumber) {
    this.registrationNumber = registrationNumber;
    return this;
  }

  public void show() {
    System.out.println("---- Automobile ----");
    System.out.println("make -> " + make);
    System.out.println("type -> " + type);
    System.out.println("maxSpeed -> " + maxSpeed);
    System.out.println("price -> " + price);
    System.out.println("mileage -> " + mileage);
    System.out.println("registrationNumber -> " + registrationNumber);
  }
}

class Car extends Automobile {
  private int noOfDoors, seatingCapacity;

  Car() {
  }

  public Car setNoOfDoors(int noOfDoors) {
    this.noOfDoors = noOfDoors;
    return this;
  }

  public Car setSeatingCapacity(int seatingCapacity) {
    this.seatingCapacity = seatingCapacity;
    return this;
  }

  public int getNoOfDoors() {
    return noOfDoors;
  }

  public int getSeatingCapacity() {
    return seatingCapacity;
  }

  @Override
  public void show() {
    System.out.println("---- Car ----");
    System.out.println("make -> " + getMake());
    System.out.println("type -> " + getType());
    System.out.println("maxSpeed -> " + getMaxSpeed());
    System.out.println("price -> " + getPrice());
    System.out.println("mileage -> " + getMileage());
    System.out.println("registrationNumber -> " + getRegistrationNumber());
    System.out.println("No of doors -> " + noOfDoors);
    System.out.println("seatingCapacity -> " + seatingCapacity);

  }
}

class Track extends Automobile {
  private int capacity, noofWheels;
  private String hoodType;

  public Track setCapacity(int capacity) {
    this.capacity = capacity;
    return this;
  }

  public Track setNoofWheels(int noofWheels) {
    this.noofWheels = noofWheels;
    return this;
  }

  public Track setHoodType(String hoodType) {
    this.hoodType = hoodType;
    return this;
  }

  public int getCapacity() {
    return capacity;
  }

  public int getNoofWheels() {
    return noofWheels;
  }

  public String getHoodType() {
    return hoodType;
  }

  @Override
  public void show() {
    System.out.println("---- Track ----");
    System.out.println("make -> " + getMake());
    System.out.println("type -> " + getType());
    System.out.println("maxSpeed -> " + getMaxSpeed());
    System.out.println("price -> " + getPrice());
    System.out.println("mileage -> " + getMileage());
    System.out.println("registrationNumber -> " + getRegistrationNumber());
    System.out.println("No of doors -> " + capacity);
    System.out.println("No of wheels -> " + noofWheels);
    System.out.println("Hood Type -> " + hoodType);
  }
}

public class Sol13 {
  public static void main(String[] args) {
    Automobile EV = new Automobile();
    EV.setType("ev").setMake("tesla").setRegistrationNumber(33221).setPrice(23232).setMileage(2.33f).setMaxSpeed(170);
    Car teslaModel3 = new Car();
    teslaModel3.setSeatingCapacity(4).setNoOfDoors(4).setMaxSpeed(12).setMileage(4.5f).setPrice(233333);
    teslaModel3.setRegistrationNumber(22321).setMake("tesla").setType("EV");
    Track tr1 = new Track();
    tr1.setType("diesel").setMake("mahindra").setRegistrationNumber(332).setPrice(3232).setMileage(5.33f)
        .setMaxSpeed(190);
    tr1.setHoodType("convertible").setCapacity(23).setNoofWheels(4);
    EV.show();
    teslaModel3.show();
    tr1.show();

  }
}
