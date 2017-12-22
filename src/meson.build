simpleconvert_sources = [
  'main.c',
  'simpleconvert-application.c',
  'simpleconvert-dialog-about.c',
  'simpleconvert-dialog-settings.c',
  'simpleconvert-notification.c',
  'simpleconvert-settings.c',
  'simpleconvert-widget-listboxitem.c',
  'simpleconvert-window-main.c',
  'simpleconvert-window-shortcuts.c'
]

simpleconvert_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('glib-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
  dependency('threads'),
  dependency('libnotify')
]

gnome = import('gnome')

simpleconvert_sources += gnome.compile_resources('simpleconvert-resources',
  'simpleconvert.gresource.xml',
  c_name: 'simpleconvert'
)

executable('simpleconvert', simpleconvert_sources,

  dependencies: simpleconvert_deps,
  install: true,
)
