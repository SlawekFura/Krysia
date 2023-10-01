#include <unistd.h>
#include "dbus_mgr_gen.h"
#include <dbus/dbus.h>

static void
print_objects (GDBusObjectManager *manager)
{
  GList *objects;
  GList *l;

  g_print ("Object manager at %s\n", g_dbus_object_manager_get_object_path (manager));
  objects = g_dbus_object_manager_get_objects (manager);
  for (l = objects; l != NULL; l = l->next)
    {
      MyNamespaceObject *object = MY_NAMESPACE_MY_OBJECT(l->data);
      GList *interfaces;
      GList *ll;
      g_print (" - Object at %s\n", g_dbus_object_get_object_path (G_DBUS_OBJECT (object)));

      interfaces = g_dbus_object_get_interfaces (G_DBUS_OBJECT (object));
      for (ll = interfaces; ll != NULL; ll = ll->next)
        {
          GDBusInterface *interface = G_DBUS_INTERFACE (ll->data);
          g_print ("   - Interface %s\n", g_dbus_interface_get_info (interface)->name);

          /* Note that @interface is really a GDBusProxy instance - and additionally also
           * an ExampleAnimal or ExampleCat instance - either of these can be used to
           * invoke methods on the remote object. For example, the generated function
           *
           *  void example_animal_call_poke_sync (ExampleAnimal  *proxy,
           *                                      gboolean        make_sad,
           *                                      gboolean        make_happy,
           *                                      GCancellable   *cancellable,
           *                                      GError        **error);
           *
           * can be used to call the Poke() D-Bus method on the .Animal interface.
           * Additionally, the generated function
           *
           *  const gchar *example_animal_get_mood (ExampleAnimal *object);
           *
           * can be used to get the value of the :Mood property.
           */
        }
      g_list_free_full (interfaces, g_object_unref);
    }
  g_list_free_full (objects, g_object_unref);
}

static void
on_object_added (GDBusObjectManager *manager,
                 GDBusObject        *object,
                 gpointer            user_data)
{
  gchar *owner;
  owner = g_dbus_object_manager_client_get_name_owner (G_DBUS_OBJECT_MANAGER_CLIENT (manager));
  g_print ("Added object at %s (owner %s)\n", g_dbus_object_get_object_path (object), owner);
  g_free (owner);
}

static void
on_object_removed (GDBusObjectManager *manager,
                   GDBusObject        *object,
                   gpointer            user_data)
{
  gchar *owner;
  owner = g_dbus_object_manager_client_get_name_owner (G_DBUS_OBJECT_MANAGER_CLIENT (manager));
  g_print ("Removed object at %s (owner %s)\n", g_dbus_object_get_object_path (object), owner);
  g_free (owner);
}

static void
on_notify_name_owner (GObject    *object,
                      GParamSpec *pspec,
                      gpointer    user_data)
{
  GDBusObjectManagerClient *manager = G_DBUS_OBJECT_MANAGER_CLIENT (object);
  gchar *name_owner;

  name_owner = g_dbus_object_manager_client_get_name_owner (manager);
  g_print ("name-owner: %s\n", name_owner);
  g_free (name_owner);
}

static void
on_interface_proxy_properties_changed (GDBusObjectManagerClient *manager,
                                       GDBusObjectProxy         *object_proxy,
                                       GDBusProxy               *interface_proxy,
                                       GVariant                 *changed_properties,
                                       const gchar *const       *invalidated_properties,
                                       gpointer                  user_data)
{
  GVariantIter iter;
  const gchar *key;
  GVariant *value;
  gchar *s;

  g_print ("Properties Changed on %s:\n", g_dbus_object_get_object_path (G_DBUS_OBJECT (object_proxy)));
  g_variant_iter_init (&iter, changed_properties);
  while (g_variant_iter_next (&iter, "{&sv}", &key, &value))
    {
      s = g_variant_print (value, TRUE);
      g_print ("  %s -> %s\n", key, s);
      g_variant_unref (value);
      g_free (s);
    }
}


void send_signal();
static DBusConnection* conn = NULL;
int setup_gdbus()
{
    DBusError err;
    int ret;
    // initialise the errors
    dbus_error_init(&err);
//  connect to the bus
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (dbus_error_is_set(&err))
    {
        printf("Connection Error (%s)\n", err.message);
        dbus_error_free(&err);
    }
    if (NULL == conn)
    {
        exit(1);
    }
// request a name on the bus
    ret = dbus_bus_request_name(conn, "test.method.server_1", DBUS_NAME_FLAG_REPLACE_EXISTING , &err);
    if (dbus_error_is_set(&err))
    {
        fprintf("Name Error (%s)\n", err.message);
        dbus_error_free(&err);
    }
    if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret)
    {
        exit(1);
    }

    return 0;
}

static char msg_interface[] = "test.signal.Type";
static char msg_name[] = "Test";
void send_signal(const char** intent)
{
    dbus_uint32_t serial = 0; // unique number to associate replies with requests
    DBusMessage* msg;
    DBusMessageIter args;

    // create a signal and check for errors 
    msg = dbus_message_new_signal("/test/signal/Type", // object name of the signal
          msg_interface, // interface name of the signal
          msg_name); // name of the signal
    if (NULL == msg)
    {
       printf("Message Null\n");
       exit(1);
    }

    // append arguments onto signal
    dbus_message_iter_init_append(msg, &args);
    if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &intent)) {
       printf("Out Of Memory!\n");
       exit(1);
    }

    // send the message and flush the connection
    if (!dbus_connection_send(conn, msg, &serial)) {
       printf("Out Of Memory!\n");
       exit(1);
    }
    dbus_connection_flush(conn);

    // free the message 
    dbus_message_unref(msg);
}

void close_dbus_connection()
{
    dbus_connection_close(conn);
}
