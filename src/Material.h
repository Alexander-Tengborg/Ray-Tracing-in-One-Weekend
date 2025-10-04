#pragma once

#include "Hittable.h"
#include "Color.h"

class Material
{
public:
    virtual ~Material() = default;

    virtual bool scatter(const Ray& incident_ray, const HitRecord& record, Color& attenuation, Ray& scattered_ray) const
    {
        return false;
    }
std::shared_ptr<int> pub;
private:
std::shared_ptr<int> pri;

protected:
std::shared_ptr<int> pro;

};

class Lambertian : public Material
{
public:
    Lambertian(const Color& albedo) : albedo_(albedo) {}

    bool scatter(const Ray& incident_ray, const HitRecord& rec, Color& attenuation, Ray& scattered_ray) const override
    {
        auto scatter_direction = rec.normal + randomUnitVector();

        // This happens if randomUnitVector() points the exact (or almost the exact)
        // opposite direction of rec.normal. If this happens, scatter_direction will be
        // very close to 0, or 0. Which is not good.
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;

        scattered_ray = Ray(rec.p, scatter_direction);

        // We could scatter with some fixed probability p and have attenuation be albedo/p
        attenuation = albedo_;

        return true;
    }

private:
    Color albedo_;
};

class Metal : public Material
{
public:
    Metal(const Color& albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray& incident_ray, const HitRecord& rec, Color& attenuation, Ray& scattered_ray) const override
    {
        auto scatter_direction = reflect(incident_ray.direction(), rec.normal);
        scatter_direction = unitVector(scatter_direction) + (fuzz_ * randomUnitVector());

        scattered_ray = Ray(rec.p, scatter_direction);

        attenuation = albedo_;

        return (dot(scatter_direction, rec.normal) > 0);
    }

private:
    Color albedo_;
    double fuzz_;
};

class Dielectric : public Material
{
public:
    Dielectric(double refraction_index) : refraction_index_(refraction_index) {}

    bool scatter(const Ray& incident_ray, const HitRecord& rec, Color& attenuation, Ray& scattered_ray) const override
    {
        attenuation = Color(1.0, 1.0, 1.0);
        double ri = rec.front_face ? (1.0/refraction_index_) : refraction_index_;

        auto unit_direction = unitVector(incident_ray.direction());
        double cos_theta = std::fmin(dot(-incident_ray.direction(), rec.normal), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

        bool cannot_refract = ri * sin_theta > 1.0;
        Vec3 direction;

        if (cannot_refract || reflectance(cos_theta, ri) > randomDouble())
            direction = reflect(unit_direction, rec.normal);
        else
            direction = refract(unit_direction, rec.normal, ri);

        scattered_ray = Ray(rec.p, direction);
        return true;
    }

private:
    // Refractive index in vacuum or air, or the ratio of the material's refractive index over
    // the refractive index of the enclosing media
    double refraction_index_;

    static double reflectance(double cos, double refraction_index)
    {
        // Use Schlick's approximation for reflectance.
        auto r0 = std::pow((1 - refraction_index) / (1 + refraction_index), 2);

        return r0 + (1 - r0) * std::pow(1 - cos, 5);
    }
};