pkgdatadir = join_paths(get_option('prefix'), get_option('datadir'), meson.project_name())
moduledir = join_paths(pkgdatadir, 'simpleconvert')
gnome = import('gnome')

gnome.compile_resources('simpleconvert',
  'simpleconvert.gresource.xml',
  gresource_bundle: true,
  install: true,
  install_dir: pkgdatadir,
)

python3 = import('python3')

conf = configuration_data()
conf.set('PYTHON', python3.find_python().path())
conf.set('VERSION', meson.project_version())
conf.set('localedir', join_paths(get_option('prefix'), get_option('localedir')))
conf.set('pkgdatadir', pkgdatadir)

configure_file(
  input: 'simpleconvert.in',
  output: 'simpleconvert',
  configuration: conf,
  install: true,
  install_dir: get_option('bindir')
)

simpleconvert_sources = [
  'widgets/ListBoxItem.py',
  'gi_composites.py',
  '__init__.py',
  'main.py',
  'SimpleconvertWindow.py',
]

install_data(simpleconvert_sources, install_dir: moduledir)
