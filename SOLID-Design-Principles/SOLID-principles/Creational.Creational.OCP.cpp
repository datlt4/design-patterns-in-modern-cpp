// open closed principle

// open for extension, closed for modification

#include <iostream>
#include <string>
#include <vector>

enum class Color
{
    red,
    green,
    blue
};

enum class Size
{
    small,
    medium,
    large
};

struct Product
{
    std::string name;
    Color color;
    Size size;
};

typedef std::vector<Product *> Items;

struct ProductFilter
{
    Items by_color(Items items, const Color color)
    {
        Items result;
        for (auto &i : items)
            if (i->color == color)
                result.push_back(i);
        return result;
    }

    Items by_size(Items items, const Size size)
    {
        Items result;
        for (auto &i : items)
            if (i->size == size)
                result.push_back(i);
        return result;
    }

    Items by_size_and_color(Items items, const Size size, const Color color)
    {
        Items result;
        for (auto &i : items)
            if (i->size == size && i->color == color)
                result.push_back(i);
        return result;
    }
};

template <typename T> struct AndSpecification;

template <typename T> struct Specification
{
    virtual ~Specification() = default;
    virtual bool is_satisfied(T *item) const = 0;

    // new: breaks OCP if you add it post-hoc
    /*AndSpecification<T> operator&&(Specification<T>&& other)
    {
      return AndSpecification<T>(*this, other);
    }*/
};

// new:
template <typename T> AndSpecification<T> operator&&(const Specification<T> &first, const Specification<T> &second)
{
    return {first, second};
}

template <typename T> struct Filter
{
    virtual std::vector<T *> filter(std::vector<T *> items, Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Product>
{
    std::vector<Product *> filter(std::vector<Product *> items, Specification<Product> &spec) override
    {
        std::vector<Product *> result;
        for (auto &p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

struct ColorSpecification : Specification<Product>
{
    Color color;

    ColorSpecification(Color color) : color(color)
    {
    }

    bool is_satisfied(Product *item) const override
    {
        return item->color == color;
    }
};

struct SizeSpecification : Specification<Product>
{
    Size size;

    explicit SizeSpecification(const Size size) : size{size}
    {
    }

    bool is_satisfied(Product *item) const override
    {
        return item->size == size;
    }
};

template <typename T> struct AndSpecification : Specification<T>
{
    const Specification<T> &first;
    const Specification<T> &second;

    AndSpecification(const Specification<T> &first, const Specification<T> &second) : first(first), second(second)
    {
    }

    bool is_satisfied(T *item) const override
    {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

// new:

int main()
{
    Product apple{"Apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};

    const Items all{&apple, &tree, &house};

    BetterFilter bf;
    ColorSpecification green(Color::green);
    Items green_things = bf.filter(all, green);
    for (Product *&x : green_things)
        std::cout << x->name << " is green" << std::endl;

    SizeSpecification large(Size::large);
    AndSpecification<Product> green_and_large(green, large);

    // auto big_green_things = bf.filter(all, green_and_large);

    // use the operator instead (same for || etc.)
    ColorSpecification spec = green && large;
    for (Product *&x : bf.filter(all, spec))
        std::cout << x->name << " is green and large" << std::endl;

    // warning: the following will compile but will NOT work
    // auto spec2 = SizeSpecification{Size::large} &&
    //              ColorSpecification{Color::blue};

    getchar();
    return 0;
}