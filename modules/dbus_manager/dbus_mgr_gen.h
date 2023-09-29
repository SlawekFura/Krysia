/*
 * Generated by gdbus-codegen 2.58.3 from dbus.xml. DO NOT EDIT.
 *
 * The license of this code is the same as for the D-Bus interface description
 * it was derived from.
 */

#ifndef __DBUS_MGR_GEN_H__
#define __DBUS_MGR_GEN_H__

#include <gio/gio.h>

G_BEGIN_DECLS


/* ------------------------------------------------------------------------ */
/* Declarations for org.gtk.GDBus.Examples.ObjectManager.MyObject */

#define MY_NAMESPACE_TYPE_MY_OBJECT (my_namespace_my_object_get_type ())
#define MY_NAMESPACE_MY_OBJECT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_MY_OBJECT, MyNamespaceMyObject))
#define MY_NAMESPACE_IS_MY_OBJECT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_MY_OBJECT))
#define MY_NAMESPACE_MY_OBJECT_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), MY_NAMESPACE_TYPE_MY_OBJECT, MyNamespaceMyObjectIface))

struct _MyNamespaceMyObject;
typedef struct _MyNamespaceMyObject MyNamespaceMyObject;
typedef struct _MyNamespaceMyObjectIface MyNamespaceMyObjectIface;

struct _MyNamespaceMyObjectIface
{
  GTypeInterface parent_iface;



  gboolean (*handle_math_op) (
    MyNamespaceMyObject *object,
    GDBusMethodInvocation *invocation,
    gboolean arg_increment,
    gboolean arg_decrement);

  const gchar * (*get_description) (MyNamespaceMyObject *object);

  const gchar * (*get_foo) (MyNamespaceMyObject *object);

  void (*inform_about_intent) (
    MyNamespaceMyObject *object,
    const gchar *arg_info);

  const gchar * (*get_bar) (MyNamespaceMyObject *object);

};

GType my_namespace_my_object_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *my_namespace_my_object_interface_info (void);
guint my_namespace_my_object_override_properties (GObjectClass *klass, guint property_id_begin);


/* D-Bus method call completion functions: */
void my_namespace_my_object_complete_math_op (
    MyNamespaceMyObject *object,
    GDBusMethodInvocation *invocation);



/* D-Bus signal emissions functions: */
void my_namespace_my_object_emit_inform_about_intent (
    MyNamespaceMyObject *object,
    const gchar *arg_info);



/* D-Bus method calls: */
void my_namespace_my_object_call_math_op (
    MyNamespaceMyObject *proxy,
    gboolean arg_increment,
    gboolean arg_decrement,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data);

gboolean my_namespace_my_object_call_math_op_finish (
    MyNamespaceMyObject *proxy,
    GAsyncResult *res,
    GError **error);

gboolean my_namespace_my_object_call_math_op_sync (
    MyNamespaceMyObject *proxy,
    gboolean arg_increment,
    gboolean arg_decrement,
    GCancellable *cancellable,
    GError **error);



/* D-Bus property accessors: */
const gchar *my_namespace_my_object_get_description (MyNamespaceMyObject *object);
gchar *my_namespace_my_object_dup_description (MyNamespaceMyObject *object);
void my_namespace_my_object_set_description (MyNamespaceMyObject *object, const gchar *value);

const gchar *my_namespace_my_object_get_foo (MyNamespaceMyObject *object);
gchar *my_namespace_my_object_dup_foo (MyNamespaceMyObject *object);
void my_namespace_my_object_set_foo (MyNamespaceMyObject *object, const gchar *value);

const gchar *my_namespace_my_object_get_bar (MyNamespaceMyObject *object);
gchar *my_namespace_my_object_dup_bar (MyNamespaceMyObject *object);
void my_namespace_my_object_set_bar (MyNamespaceMyObject *object, const gchar *value);


/* ---- */

#define MY_NAMESPACE_TYPE_MY_OBJECT_PROXY (my_namespace_my_object_proxy_get_type ())
#define MY_NAMESPACE_MY_OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_MY_OBJECT_PROXY, MyNamespaceMyObjectProxy))
#define MY_NAMESPACE_MY_OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), MY_NAMESPACE_TYPE_MY_OBJECT_PROXY, MyNamespaceMyObjectProxyClass))
#define MY_NAMESPACE_MY_OBJECT_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), MY_NAMESPACE_TYPE_MY_OBJECT_PROXY, MyNamespaceMyObjectProxyClass))
#define MY_NAMESPACE_IS_MY_OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_MY_OBJECT_PROXY))
#define MY_NAMESPACE_IS_MY_OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), MY_NAMESPACE_TYPE_MY_OBJECT_PROXY))

typedef struct _MyNamespaceMyObjectProxy MyNamespaceMyObjectProxy;
typedef struct _MyNamespaceMyObjectProxyClass MyNamespaceMyObjectProxyClass;
typedef struct _MyNamespaceMyObjectProxyPrivate MyNamespaceMyObjectProxyPrivate;

struct _MyNamespaceMyObjectProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  MyNamespaceMyObjectProxyPrivate *priv;
};

struct _MyNamespaceMyObjectProxyClass
{
  GDBusProxyClass parent_class;
};

GType my_namespace_my_object_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (MyNamespaceMyObjectProxy, g_object_unref)
#endif

void my_namespace_my_object_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
MyNamespaceMyObject *my_namespace_my_object_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
MyNamespaceMyObject *my_namespace_my_object_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void my_namespace_my_object_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
MyNamespaceMyObject *my_namespace_my_object_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
MyNamespaceMyObject *my_namespace_my_object_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define MY_NAMESPACE_TYPE_MY_OBJECT_SKELETON (my_namespace_my_object_skeleton_get_type ())
#define MY_NAMESPACE_MY_OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_MY_OBJECT_SKELETON, MyNamespaceMyObjectSkeleton))
#define MY_NAMESPACE_MY_OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), MY_NAMESPACE_TYPE_MY_OBJECT_SKELETON, MyNamespaceMyObjectSkeletonClass))
#define MY_NAMESPACE_MY_OBJECT_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), MY_NAMESPACE_TYPE_MY_OBJECT_SKELETON, MyNamespaceMyObjectSkeletonClass))
#define MY_NAMESPACE_IS_MY_OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_MY_OBJECT_SKELETON))
#define MY_NAMESPACE_IS_MY_OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), MY_NAMESPACE_TYPE_MY_OBJECT_SKELETON))

typedef struct _MyNamespaceMyObjectSkeleton MyNamespaceMyObjectSkeleton;
typedef struct _MyNamespaceMyObjectSkeletonClass MyNamespaceMyObjectSkeletonClass;
typedef struct _MyNamespaceMyObjectSkeletonPrivate MyNamespaceMyObjectSkeletonPrivate;

struct _MyNamespaceMyObjectSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  MyNamespaceMyObjectSkeletonPrivate *priv;
};

struct _MyNamespaceMyObjectSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType my_namespace_my_object_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (MyNamespaceMyObjectSkeleton, g_object_unref)
#endif

MyNamespaceMyObject *my_namespace_my_object_skeleton_new (void);


/* ------------------------------------------------------------------------ */
/* Declarations for org.gtk.GDBus.Examples.ObjectManager.Another */

#define MY_NAMESPACE_TYPE_ANOTHER (my_namespace_another_get_type ())
#define MY_NAMESPACE_ANOTHER(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_ANOTHER, MyNamespaceAnother))
#define MY_NAMESPACE_IS_ANOTHER(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_ANOTHER))
#define MY_NAMESPACE_ANOTHER_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), MY_NAMESPACE_TYPE_ANOTHER, MyNamespaceAnotherIface))

struct _MyNamespaceAnother;
typedef struct _MyNamespaceAnother MyNamespaceAnother;
typedef struct _MyNamespaceAnotherIface MyNamespaceAnotherIface;

struct _MyNamespaceAnotherIface
{
  GTypeInterface parent_iface;
};

GType my_namespace_another_get_type (void) G_GNUC_CONST;

GDBusInterfaceInfo *my_namespace_another_interface_info (void);
guint my_namespace_another_override_properties (GObjectClass *klass, guint property_id_begin);


/* ---- */

#define MY_NAMESPACE_TYPE_ANOTHER_PROXY (my_namespace_another_proxy_get_type ())
#define MY_NAMESPACE_ANOTHER_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_ANOTHER_PROXY, MyNamespaceAnotherProxy))
#define MY_NAMESPACE_ANOTHER_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), MY_NAMESPACE_TYPE_ANOTHER_PROXY, MyNamespaceAnotherProxyClass))
#define MY_NAMESPACE_ANOTHER_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), MY_NAMESPACE_TYPE_ANOTHER_PROXY, MyNamespaceAnotherProxyClass))
#define MY_NAMESPACE_IS_ANOTHER_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_ANOTHER_PROXY))
#define MY_NAMESPACE_IS_ANOTHER_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), MY_NAMESPACE_TYPE_ANOTHER_PROXY))

typedef struct _MyNamespaceAnotherProxy MyNamespaceAnotherProxy;
typedef struct _MyNamespaceAnotherProxyClass MyNamespaceAnotherProxyClass;
typedef struct _MyNamespaceAnotherProxyPrivate MyNamespaceAnotherProxyPrivate;

struct _MyNamespaceAnotherProxy
{
  /*< private >*/
  GDBusProxy parent_instance;
  MyNamespaceAnotherProxyPrivate *priv;
};

struct _MyNamespaceAnotherProxyClass
{
  GDBusProxyClass parent_class;
};

GType my_namespace_another_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (MyNamespaceAnotherProxy, g_object_unref)
#endif

void my_namespace_another_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
MyNamespaceAnother *my_namespace_another_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error);
MyNamespaceAnother *my_namespace_another_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);

void my_namespace_another_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data);
MyNamespaceAnother *my_namespace_another_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
MyNamespaceAnother *my_namespace_another_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error);


/* ---- */

#define MY_NAMESPACE_TYPE_ANOTHER_SKELETON (my_namespace_another_skeleton_get_type ())
#define MY_NAMESPACE_ANOTHER_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_ANOTHER_SKELETON, MyNamespaceAnotherSkeleton))
#define MY_NAMESPACE_ANOTHER_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), MY_NAMESPACE_TYPE_ANOTHER_SKELETON, MyNamespaceAnotherSkeletonClass))
#define MY_NAMESPACE_ANOTHER_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), MY_NAMESPACE_TYPE_ANOTHER_SKELETON, MyNamespaceAnotherSkeletonClass))
#define MY_NAMESPACE_IS_ANOTHER_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_ANOTHER_SKELETON))
#define MY_NAMESPACE_IS_ANOTHER_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), MY_NAMESPACE_TYPE_ANOTHER_SKELETON))

typedef struct _MyNamespaceAnotherSkeleton MyNamespaceAnotherSkeleton;
typedef struct _MyNamespaceAnotherSkeletonClass MyNamespaceAnotherSkeletonClass;
typedef struct _MyNamespaceAnotherSkeletonPrivate MyNamespaceAnotherSkeletonPrivate;

struct _MyNamespaceAnotherSkeleton
{
  /*< private >*/
  GDBusInterfaceSkeleton parent_instance;
  MyNamespaceAnotherSkeletonPrivate *priv;
};

struct _MyNamespaceAnotherSkeletonClass
{
  GDBusInterfaceSkeletonClass parent_class;
};

GType my_namespace_another_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (MyNamespaceAnotherSkeleton, g_object_unref)
#endif

MyNamespaceAnother *my_namespace_another_skeleton_new (void);


/* ---- */

#define MY_NAMESPACE_TYPE_OBJECT (my_namespace_object_get_type ())
#define MY_NAMESPACE_OBJECT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_OBJECT, MyNamespaceObject))
#define MY_NAMESPACE_IS_OBJECT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_OBJECT))
#define MY_NAMESPACE_OBJECT_GET_IFACE(o) (G_TYPE_INSTANCE_GET_INTERFACE ((o), MY_NAMESPACE_TYPE_OBJECT, MyNamespaceObject))

struct _MyNamespaceObject;
typedef struct _MyNamespaceObject MyNamespaceObject;
typedef struct _MyNamespaceObjectIface MyNamespaceObjectIface;

struct _MyNamespaceObjectIface
{
  GTypeInterface parent_iface;
};

GType my_namespace_object_get_type (void) G_GNUC_CONST;

MyNamespaceMyObject *my_namespace_object_get_my_object (MyNamespaceObject *object);
MyNamespaceAnother *my_namespace_object_get_another (MyNamespaceObject *object);
MyNamespaceMyObject *my_namespace_object_peek_my_object (MyNamespaceObject *object);
MyNamespaceAnother *my_namespace_object_peek_another (MyNamespaceObject *object);

#define MY_NAMESPACE_TYPE_OBJECT_PROXY (my_namespace_object_proxy_get_type ())
#define MY_NAMESPACE_OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_OBJECT_PROXY, MyNamespaceObjectProxy))
#define MY_NAMESPACE_OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), MY_NAMESPACE_TYPE_OBJECT_PROXY, MyNamespaceObjectProxyClass))
#define MY_NAMESPACE_OBJECT_PROXY_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), MY_NAMESPACE_TYPE_OBJECT_PROXY, MyNamespaceObjectProxyClass))
#define MY_NAMESPACE_IS_OBJECT_PROXY(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_OBJECT_PROXY))
#define MY_NAMESPACE_IS_OBJECT_PROXY_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), MY_NAMESPACE_TYPE_OBJECT_PROXY))

typedef struct _MyNamespaceObjectProxy MyNamespaceObjectProxy;
typedef struct _MyNamespaceObjectProxyClass MyNamespaceObjectProxyClass;
typedef struct _MyNamespaceObjectProxyPrivate MyNamespaceObjectProxyPrivate;

struct _MyNamespaceObjectProxy
{
  /*< private >*/
  GDBusObjectProxy parent_instance;
  MyNamespaceObjectProxyPrivate *priv;
};

struct _MyNamespaceObjectProxyClass
{
  GDBusObjectProxyClass parent_class;
};

GType my_namespace_object_proxy_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (MyNamespaceObjectProxy, g_object_unref)
#endif

MyNamespaceObjectProxy *my_namespace_object_proxy_new (GDBusConnection *connection, const gchar *object_path);

#define MY_NAMESPACE_TYPE_OBJECT_SKELETON (my_namespace_object_skeleton_get_type ())
#define MY_NAMESPACE_OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_OBJECT_SKELETON, MyNamespaceObjectSkeleton))
#define MY_NAMESPACE_OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), MY_NAMESPACE_TYPE_OBJECT_SKELETON, MyNamespaceObjectSkeletonClass))
#define MY_NAMESPACE_OBJECT_SKELETON_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), MY_NAMESPACE_TYPE_OBJECT_SKELETON, MyNamespaceObjectSkeletonClass))
#define MY_NAMESPACE_IS_OBJECT_SKELETON(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_OBJECT_SKELETON))
#define MY_NAMESPACE_IS_OBJECT_SKELETON_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), MY_NAMESPACE_TYPE_OBJECT_SKELETON))

typedef struct _MyNamespaceObjectSkeleton MyNamespaceObjectSkeleton;
typedef struct _MyNamespaceObjectSkeletonClass MyNamespaceObjectSkeletonClass;
typedef struct _MyNamespaceObjectSkeletonPrivate MyNamespaceObjectSkeletonPrivate;

struct _MyNamespaceObjectSkeleton
{
  /*< private >*/
  GDBusObjectSkeleton parent_instance;
  MyNamespaceObjectSkeletonPrivate *priv;
};

struct _MyNamespaceObjectSkeletonClass
{
  GDBusObjectSkeletonClass parent_class;
};

GType my_namespace_object_skeleton_get_type (void) G_GNUC_CONST;

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (MyNamespaceObjectSkeleton, g_object_unref)
#endif

MyNamespaceObjectSkeleton *my_namespace_object_skeleton_new (const gchar *object_path);
void my_namespace_object_skeleton_set_my_object (MyNamespaceObjectSkeleton *object, MyNamespaceMyObject *interface_);
void my_namespace_object_skeleton_set_another (MyNamespaceObjectSkeleton *object, MyNamespaceAnother *interface_);

/* ---- */

#define MY_NAMESPACE_TYPE_OBJECT_MANAGER_CLIENT (my_namespace_object_manager_client_get_type ())
#define MY_NAMESPACE_OBJECT_MANAGER_CLIENT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), MY_NAMESPACE_TYPE_OBJECT_MANAGER_CLIENT, MyNamespaceObjectManagerClient))
#define MY_NAMESPACE_OBJECT_MANAGER_CLIENT_CLASS(k) (G_TYPE_CHECK_CLASS_CAST ((k), MY_NAMESPACE_TYPE_OBJECT_MANAGER_CLIENT, MyNamespaceObjectManagerClientClass))
#define MY_NAMESPACE_OBJECT_MANAGER_CLIENT_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), MY_NAMESPACE_TYPE_OBJECT_MANAGER_CLIENT, MyNamespaceObjectManagerClientClass))
#define MY_NAMESPACE_IS_OBJECT_MANAGER_CLIENT(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), MY_NAMESPACE_TYPE_OBJECT_MANAGER_CLIENT))
#define MY_NAMESPACE_IS_OBJECT_MANAGER_CLIENT_CLASS(k) (G_TYPE_CHECK_CLASS_TYPE ((k), MY_NAMESPACE_TYPE_OBJECT_MANAGER_CLIENT))

typedef struct _MyNamespaceObjectManagerClient MyNamespaceObjectManagerClient;
typedef struct _MyNamespaceObjectManagerClientClass MyNamespaceObjectManagerClientClass;
typedef struct _MyNamespaceObjectManagerClientPrivate MyNamespaceObjectManagerClientPrivate;

struct _MyNamespaceObjectManagerClient
{
  /*< private >*/
  GDBusObjectManagerClient parent_instance;
  MyNamespaceObjectManagerClientPrivate *priv;
};

struct _MyNamespaceObjectManagerClientClass
{
  GDBusObjectManagerClientClass parent_class;
};

#if GLIB_CHECK_VERSION(2, 44, 0)
G_DEFINE_AUTOPTR_CLEANUP_FUNC (MyNamespaceObjectManagerClient, g_object_unref)
#endif

GType my_namespace_object_manager_client_get_type (void) G_GNUC_CONST;

GType my_namespace_object_manager_client_get_proxy_type (GDBusObjectManagerClient *manager, const gchar *object_path, const gchar *interface_name, gpointer user_data);

void my_namespace_object_manager_client_new (
    GDBusConnection        *connection,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GAsyncReadyCallback     callback,
    gpointer                user_data);
GDBusObjectManager *my_namespace_object_manager_client_new_finish (
    GAsyncResult        *res,
    GError             **error);
GDBusObjectManager *my_namespace_object_manager_client_new_sync (
    GDBusConnection        *connection,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GError                **error);

void my_namespace_object_manager_client_new_for_bus (
    GBusType                bus_type,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GAsyncReadyCallback     callback,
    gpointer                user_data);
GDBusObjectManager *my_namespace_object_manager_client_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error);
GDBusObjectManager *my_namespace_object_manager_client_new_for_bus_sync (
    GBusType                bus_type,
    GDBusObjectManagerClientFlags  flags,
    const gchar            *name,
    const gchar            *object_path,
    GCancellable           *cancellable,
    GError                **error);


G_END_DECLS

#endif /* __DBUS_MGR_GEN_H__ */
