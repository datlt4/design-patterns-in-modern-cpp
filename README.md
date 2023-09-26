# Design Patterns In Modern Cpp

## Format C++ code

```bash
apt install clang-format -y
clang-format -style=microsoft -dump-config > .clang-format
sed -i 's/AlwaysBreakTemplateDeclarations: MultiLine/AlwaysBreakTemplateDeclarations: false/g' .clang-format

# To use
find . -regex '.*\.\(c\|cc\|cpp\|cxx\|cu\|h\|hh\|hpp\|hxx\|inl\|inc\|ipp\|m\|mm\)$' -exec clang-format -style=file -i {} \;
```

## Pre-commit

```bash
python3 -m pip install pre-commit
pre-commit install      # runs every time you commit in git
pre-commit run -a       # To use
pre-commit autoupdate   # To update this file
```

# SOLID Design Principles

The SOLID principles are a set of five design principles that are intended to help software developers create more maintainable and scalable software.

## Single Responsibility Principle (SRP)

- A class should have only one reason to change.

- It means that a class should have a single responsibility, and all its services should be narrowly aligned with that responsibility.

- This principle encourages the separation of concerns and helps in making classes and methods easier to understand and maintain.

## Open-Closed Principle (OCP)

- Software entities (classes, modules, functions) should be open for extension but closed for modification.

- It encourages developers to design their software components in a way that allows for adding new functionality (extension) without changing existing code (modification).

- Achieved through the use of interfaces, abstract classes, and polymorphism.

## Liskov Substitution Principle (LSP)

- Objects of a derived class must be able to replace objects of the base class without affecting the correctness of the program.

- In other words, a derived class should be substitutable for its base class without altering the desirable properties of the program.

- Ensures that inheritance hierarchies are well-designed and don't introduce unexpected behavior.

## Interface Segregation Principle (ISP)

## Dependency Inversion Principle (DIP)
