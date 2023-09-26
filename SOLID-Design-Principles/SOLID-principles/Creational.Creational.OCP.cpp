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

/**
 * Represents a product with a name, color, and size.
 */
struct Product
{
    std::string name;
    Color color;
    Size size;
};

/**
 * Alias for a vector of pointers to Product objects.
 */
typedef std::vector<Product *> Items;

/**
 * Contains methods to filter a collection of products based on color, size, or both.
 * @param: a collection of products
 * @return: a filtered collection
 */
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

/**
 * A generic interface for defining product specifications.
 */
template <typename T> struct Specification
{
    virtual ~Specification() = default;
    virtual bool is_satisfied(T *item) const = 0;

    // new: breaks OCP if you add it post-hoc
    // AndSpecification<T> operator&&(Specification<T>&& other)
    // {
    //     return AndSpecification<T>(*this, other);
    // }
};

/**
 * Specifications that check if a product's color matches a specified criterion.
 */
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

/**
 * Specifications that check if a product's size matches a specified criterion.
 */
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

/**
 * Allows combining two specifications using logical AND.
 */
template <typename T> struct AndSpecification;

/**
 * Ensures that a product satisfies both specifications for color and size.
 */
template <typename T> AndSpecification<T> operator&&(const Specification<T> &first, const Specification<T> &second)
{
    return {first, second};
}

/**
 * Implement the filtering process for products based on specifications.
 * An interface that defines a method to filter a collection of items based on a specification.
 */
template <typename T> struct Filter
{
    virtual std::vector<T *> filter(std::vector<T *> items, Specification<T> &spec) = 0;
};

/**
 * A concrete implementation of Filter for Product items.
 */
struct BetterFilter : Filter<Product>
{
    Items filter(Items items, Specification<Product> &spec) override
    {
        Items result;
        for (auto &p : items)
            if (spec.is_satisfied(p))
                result.push_back(p);
        return result;
    }
};

// new:
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

/**
 * The code allows for the extension of functionality without modifying existing classes. It achieves this through the
 * use of abstract base classes (`Specification<T>`) and the ability to create new concrete classes that implement these
 * specifications. For example, you can create new `ColorSpecification` and `SizeSpecification` classes without changing
 * the existing `Filter` or `BetterFilter` classes.
 *
 * The existing classes (`Filter`, `BetterFilter`, `Specification`, etc.) are designed in a way that they don't need to
 * be modified when adding new filtering criteria
 */

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
    for (Product *&x : bf.filter(all, green_and_large))
        std::cout << x->name << " is green and large" << std::endl;

    // use the operator instead (same for || etc.)
    AndSpecification<Product> spec = (green && large);
    for (Product *&x : bf.filter(all, spec))
        std::cout << x->name << " is green and large" << std::endl;

    // warning: the following will compile but will NOT work
    // auto spec2 = SizeSpecification{Size::large} &&
    //              ColorSpecification{Color::blue};

    getchar();
    return 0;
}
