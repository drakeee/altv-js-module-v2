#include "Class.h"
#include "interfaces/IResource.h"

static void Current(js::PropertyContext& ctx)
{
    js::IResource* resource = ctx.GetResource();
    if(!resource || !resource->GetResource())
    {
        ctx.Return(nullptr);
        return;
    }
    v8::Local<v8::Object> resourceObj = resource->CreateResourceObject(resource->GetResource());
    ctx.Return(resourceObj);
}

static void All(js::PropertyContext& ctx)
{
    js::IResource* resource = ctx.GetResource();

    std::vector<alt::IResource*> resources = alt::ICore::Instance().GetAllResources();
    js::Array arr(resources.size());
    for(auto res : resources) arr.Push(resource->CreateResourceObject(res));
    ctx.Return(arr);
}

static void Get(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;
    js::IResource* resource = ctx.GetResource();

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::IResource* res = alt::ICore::Instance().GetResource(resourceName);
    if(!res)
    {
        ctx.Return(nullptr);
        return;
    }
    v8::Local<v8::Object> resourceObj = resource->CreateResourceObject(res);
    ctx.Return(resourceObj);
}

static void Exists(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::IResource* resource = alt::ICore::Instance().GetResource(resourceName);
    ctx.Return(resource != nullptr);
}

static void Start(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::ICore::Instance().StartResource(resourceName);
}

static void Stop(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::ICore::Instance().StopResource(resourceName);
}

static void Restart(js::FunctionContext& ctx)
{
    if(!ctx.CheckArgCount(1)) return;

    std::string resourceName;
    if(!ctx.GetArg(0, resourceName)) return;

    alt::ICore::Instance().RestartResource(resourceName);
}

static void TypeGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetType());
}

static void PathGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetPath());
}

static void NameGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetName());
}

static void MainGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->GetMain());
}

static void ExportsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(js::MValueToJS(resource->GetExports()));
}

static void DependenciesGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    std::vector<std::string> dependencies;
    for(auto& dependency : resource->GetDependencies())
    {
        dependencies.push_back(dependency);
    }
    ctx.Return(dependencies);
}

static void DependantsGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    std::vector<std::string> dependants;
    for(auto& dependant : resource->GetDependants())
    {
        dependants.push_back(dependant);
    }
    ctx.Return(dependants);
}

static void IsStartedGetter(js::PropertyContext& ctx)
{
    if(!ctx.CheckExtraInternalFieldValue()) return;

    alt::IResource* resource = ctx.GetExtraInternalFieldValue<alt::IResource>();
    ctx.Return(resource->IsStarted());
}

// clang-format off
extern js::Class resourceClass("Resource", nullptr, [](js::ClassTemplate& tpl)
{
    tpl.StaticProperty("current", Current);
    tpl.StaticProperty("all", All);

    tpl.StaticFunction("get", Get);
    tpl.StaticFunction("exists", Exists);
    tpl.StaticFunction("start", Start);
    tpl.StaticFunction("stop", Stop);
    tpl.StaticFunction("restart", Restart);

    tpl.Property("type", TypeGetter);
    tpl.Property("path", PathGetter);
    tpl.Property("name", NameGetter);
    tpl.Property("main", MainGetter);
    tpl.Property("exports", ExportsGetter);
    tpl.Property("dependencies", DependenciesGetter);
    tpl.Property("dependants", DependantsGetter);
    tpl.Property("isStarted", IsStartedGetter);
}, true);
