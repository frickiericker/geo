#include <chrono>
#include <iostream>
#include <type_traits>
#include <random>
#include <vector>

#include <cstring>

#include <geo/all.hpp>

using kernel = geo::standard_kernel<double, 3>;
using point_t = geo::point<kernel>;
using vector_t = geo::vector<kernel>;
using index_t = std::vector<point_t>::size_type;

double evaluate_lennard_jones_potential(double r2)
{
    constexpr double sigma = 0.001;
    double const u2 = (sigma * sigma) / r2;
    double const u4 = u2 * u2;
    double const u6 = u2 * u4;
    return (u6 - 1) * u6;
}

// vector<geo::point>
double compute_potential_energy(std::vector<point_t> const& points)
{
    index_t const n_points = points.size();
    double energy = 0;
    for (index_t i = 0; i < n_points; ++i) {
        for (index_t j = i + 1; j < n_points; ++j) {
            double const r2 = squared_distance(points[i], points[j]);
            energy += evaluate_lennard_jones_potential(r2);
        }
    }
    return energy;
}

// Raw array
template<index_t N>
double compute_potential_energy(double const(& points)[N][3])
{
    double energy = 0;
    for (index_t i = 0; i < N; ++i) {
        for (index_t j = i + 1; j < N; ++j) {
            double const dx = points[i][0] - points[j][0];
            double const dy = points[i][1] - points[j][1];
            double const dz = points[i][2] - points[j][2];
            double const r2 = dx * dx + dy * dy + dz * dz;
            energy += evaluate_lennard_jones_potential(r2);
        }
    }
    return energy;
}

std::vector<point_t> generate_points(index_t n_points)
{
    std::vector<point_t> points;

    std::seed_seq seed{1, 2, 3, 4};
    std::mt19937_64 engine{seed};
    std::uniform_real_distribution<double> coord_dist;

    for (index_t i = 0; i < n_points; ++i) {
        point_t point;
        for (double& coord : point) {
            coord = coord_dist(engine);
        }
        points.push_back(point);
    }
    return points;
}

template<typename X>
void measure(X const& points, int n_measures)
{
    double energy = 0;

    auto const t_start = std::chrono::steady_clock::now();
    for (long n = 0; n < n_measures; ++n) {
        energy += compute_potential_energy(points);
    }
    auto const t_finish = std::chrono::steady_clock::now();

    auto const time = t_finish - t_start;
    auto const time_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(time).count();
    auto const mean_time_ms = 1.0e-6 * time_ns / n_measures;

    energy /= n_measures;

    std::cout << "Mean time: " << mean_time_ms << " ms\n";
    std::cout << "Energy: " << energy << '\n';
    std::cout << '\n';
}

int main()
{
    constexpr index_t n_points = 10000;
    constexpr int n_measures = 10;

    std::cout << "Number of points: " << n_points << '\n';
    std::cout << "Number of measurements: " << n_measures << '\n';
    std::cout << '\n';

    std::vector<point_t> const points_vector = generate_points(n_points);

    static_assert(std::is_trivially_copyable<point_t>::value, "");
    static_assert(sizeof(point_t) == sizeof(double[point_t::dimension]), "");
    double points_array[n_points][point_t::dimension];
    std::memcpy(points_array, points_vector.data(), sizeof(points_array));

    std::cout << "vector<geo::point>\n";
    measure(points_vector, n_measures);

    std::cout << "Raw array\n";
    measure(points_array, n_measures);
}
