# Design Patterns In Modern Cpp

## Format C++ code

```bash
apt install clang-format -y
clang-format -style=microsoft -dump-config > .clang-format
sed -i 's/AlwaysBreakTemplateDeclarations: MultiLine/AlwaysBreakTemplateDeclarations: Yes/g' .clang-format

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


## Liskov Substitution Principle (LSP)


## Interface Segregation Principle (ISP)


## Dependency Inversion Principle (DIP)


