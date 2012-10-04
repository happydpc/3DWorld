// 3D World - Global Function Registry Header
// by Frank Gennari
// 9/8/12

#ifndef _FUNCTION_REGISTRY_H_
#define _FUNCTION_REGISTRY_H_

#include "3DWorld.h"


// function prototypes - main (3DWorld.cpp, etc.)
bool check_gl_error(unsigned loc_id);
void enable_blend();
void disable_blend();
void set_array_client_state(bool va, bool tca, bool na, bool ca);
void set_lighted_sides(int num);
void enable_point_specular();
void disable_point_specular();
void reset_fog();
void set_light_atten(int light, float attenuation=1.0);
void set_perspective(float fovy, float nc_scale);
float get_moon_light_factor();
void setup_basic_fog();
void check_zoom();
void reset_camera_pos();
void update_cpos();
void advance_camera(int dir);
bool open_file(FILE *&fp, char const *const fn, std::string const &file_type, char const *const mode="r");
void fire_weapon();
bool has_extension(std::string const &ext);

// function prototypes - visibility
void calc_mesh_shadows(unsigned l, point const &lpos, float const *const mh, unsigned char *smask, int xsize, int ysize,
					   float const *sh_in_x=NULL, float const *sh_in_y=NULL, float *sh_out_x=NULL, float *sh_out_y=NULL);
void calc_visibility(unsigned light_sources);
bool is_visible_to_light_cobj(point const &pos, int light, float radius, int cobj, int skip_dynamic, int *cobj_ix=NULL);
bool coll_pt_vis_test(point pos, point pos2, float dist, int &index, int cobj, int skip_dynamic, int test_alpha);
void calc_view_test_terms(float &tterm, float &sterm, bool is_zoomed);
void calc_viewing_cone();
void set_camera_pdu();
bool sphere_cobj_occluded(point const &viewer, point const &sc, float radius);
bool sphere_in_view(pos_dir_up const &pdu, point const &pos, float radius, int max_level, bool no_frustum_test=0);
int  get_light_pos(point &lpos, int light);
void update_sun_shadows();
void create_shadows();
void update_sun_and_moon();
int light_valid(unsigned light_sources, int l, point &lpos);

// function prototypes - shadows
void add_cobj_shadows(unsigned light_sources);
int  camera_shadow(point const &camera);
int  get_shape_shadow_bb(point const *points, int npoints, int l, int quality, point const &lpos,
	int &xmin, int &ymin, int &xmax, int &ymax, int &ret_val, unsigned char stype);
void get_sphere_points(point const &pos, float radius, point *pts, unsigned npts, vector3d const &dir);
int  enable_shadow_envelope(point const &pos, float radius, unsigned light_sources, int is_dynamic);
void disable_shadow_envelope(unsigned light_sources);
int  sphere_shadow2(point const &pos, float radius, unsigned light_sources, int is_dynamic, int quality);
int  sphere_shadow(point const &pos, float radius, unsigned light_sources, int is_dynamic, int quality);
int  cylinder_shadow(point p1, point p2, float radius1, float radius2, unsigned light_sources, int shadow_ends, int is_dynamic, int quality);
int  polygon_shadow(point const *points, vector3d const &norm, int npoints, float thick, unsigned light_sources,
					int is_dynamic, int quality, int is_cube, int tid=-1);
int  cube_shadow(cube_t const &cube, unsigned light_sources, int is_dynamic, int quality);
void reset_shadows(unsigned char type);

// function prototypes - mesh_intersect
bool sphere_visible_to_pt(point const &pt, point const &center, float radius);
bool is_visible_from_light(point const &pos, point const &lpos, int fast);
bool line_intersect_surface_cached(point const &v1, point const &v2, int &xpos, int &ypos, float &zval, int fast=0);
bool line_intersect_mesh(point const &v1, point const &v2, int &xpos, int &ypos, float &zval, int fast=0, bool cached=0);
bool line_intersect_mesh(point const &v1, point const &v2, int fast=0);
void gen_mesh_bsp_tree();

// function prototypes - build_world
void create_object_groups();
bool is_rain_enabled();
void shift_all_objs(vector3d const &vd);
void process_platforms();
void process_groups();
void gen_scene(int generate_mesh, int gen_trees, int keep_sin_table, int update_zvals, int rgt_only);
void init_models();
void free_models();

// function prototypes - display_world
point get_sun_pos();
point get_moon_pos();
colorRGBA get_bkg_color(point const &p1, vector3d const &v12);

// function prototypes - draw_world
void set_fill_mode();
int get_universe_ambient_light();
void set_gl_light_pos(int light, point const &pos, float w);
void set_colors_and_enable_light(int light, float const ambient[4], float const diffuse[4]);
void clear_colors_and_disable_light(int light);
int get_light();
void get_shadowed_color(colorRGBA &color_a, point const &pos, bool &is_shadowed, bool precip, bool no_dynamic);
bool pt_is_shadowed(point const &pos, int light, float radius, int cid, bool fast, bool use_mesh);
void set_color_alpha(colorRGBA color, float alpha=1.0);
void draw_camera_weapon(bool want_has_trans);
void draw_solid_object_groups();
void draw_transparent_object_groups();
void draw_select_groups(int solid);
colorRGBA get_powerup_color(int powerup);
void draw_shadow_volume(point const &pos, point const &lpos, float radius, int &inverts);
int  draw_shadowed_objects(int light);
void set_specular(float specularity, float shininess);
colorRGBA get_glowing_obj_color(point const &pos, int time, int lifetime, float &stime, bool shrapnel_cscale, bool fade);
colorRGBA const &get_landmine_light_color(int time);
float get_landmine_sensor_height(float radius, int time);
colorRGBA get_plasma_color(float size);
void upload_mvm_to_shader(shader_t &s, char const *const var_name);
void set_dlights_booleans(shader_t &s, bool enable, int shader_type);
void set_indir_lighting_block(shader_t &s, bool use_smoke_indir);
colorRGBA setup_smoke_shaders(shader_t &s, float min_alpha, int use_texgen, bool keep_alpha, bool indir_lighting, bool direct_lighting,
	bool dlights, bool smoke_en, bool has_lt_atten=0, bool use_smap=0, bool use_bmap=0, bool use_spec_map=0, bool use_mvm=0, bool force_tsl=0);
void end_smoke_shaders(shader_t &s, colorRGBA const &orig_fog_color);
void set_tree_branch_shader(shader_t &s, bool direct_lighting, bool dlights, bool use_smap, bool use_geom_shader);
void setup_procedural_shaders(shader_t &s, float min_alpha, bool indir_lighting, bool dlights, bool use_smap, bool use_noise_tex,
	float tex_scale=1.0, float noise_scale=1.0, float tex_mix_saturate=1.0);
void setup_object_render_data();
void end_group(int &last_group_id);
void draw_coll_surfaces(bool draw_solid, bool draw_trans);
void draw_stars(float alpha);
void draw_sun();
void draw_moon();
void draw_earth();
void draw_stationary_earth(float radius);
void apply_red_sky(colorRGBA &color);
colorRGBA get_cloud_color();
float get_cloud_density(point const &pt, vector3d const &dir);
void free_cloud_textures();
void draw_puffy_clouds(int order);
float get_cloud_zmax();
void set_cloud_uniforms(shader_t &s, unsigned tu_id);
void draw_cloud_plane(bool reflection_pass);
void draw_sky(int order);
void draw_stationary_sky(float radius, float density);
void compute_brightness();
void draw_water_plane(float zval, unsigned reflection_tid);
void draw_bubbles();
void draw_smoke();
void draw_fires();
void draw_decals();
void add_camera_filter(colorRGBA const &color, unsigned time, int tid, unsigned ix);
void draw_camera_filters(vector<camera_filter> &cfs);
void draw_projectile_effects();
void draw_env_other();
void mouse_draw_on_ground(int x, int y);
void draw_splash(float x, float y, float z, float size, colorRGBA color=WATER_C);
void draw_text(float x, float y, float z, char const *text, float tsize=1.0, bool bitmap_font=0);
void draw_framerate(float val);
void draw_compass_and_alt();
void exec_universe_text(std::string const &text);

// function prototypes - draw shapes
bool is_above_mesh(point const &pos);
bool check_face_containment(cube_t const &cube, int dim, int dir, int cobj);
float get_mesh_zmax(point const *const pts, unsigned npts);
void add_shadow_obj(point const &pos, float radius, int coll_id);
void add_coll_shadow_objs();
void get_occluders();

// function prototypes - draw primitives
void get_ortho_vectors(vector3d const &v12, vector3d *vab, int force_dim=-1);
vector_point_norm const &gen_cylinder_data(point const ce[2], float radius1, float radius2, unsigned ndiv, vector3d &v12,
										   float const *const perturb_map=NULL, float s_beg=0.0, float s_end=1.0, int force_dim=-1);
void draw_cylinder(float length, float radius1, float radius2, int ndiv, int nstacks, bool draw_ends, bool first_end_only=0, bool last_end_only=0);
void draw_cylinder_nstacks(float len, float r1, float r2, int ndiv, int nstacks, bool texture);
void draw_cylinder(point const &p1, float length, float radius1, float radius2, int ndiv, int nstacks, bool draw_ends);
void draw_circle_normal(float r_inner, float r_outer, int ndiv, int invert_normals);
void draw_circle_normal_at_z(float z, float r_inner, float r_outer, int ndiv, int invert_normals);
void draw_rotated_cylinder(point const &p1, point const &p2, float radius1, float radius2, int ndiv, int nstacks,
						   bool draw_ends, vector3d const &scale=zero_vector);
void draw_fast_cylinder(point const &p1, point const &p2, float radius1, float radius2, int ndiv, bool texture, int draw_sides_ends=0,
						float const *const perturb_map=NULL, bool const *const render_map=NULL, float const *const exp_map=NULL,
						point const *const pt_shift=NULL, float expand=0.0, float s_beg=0.0, float s_end=1.0);
void draw_cylindrical_section(point const &pos, float length, float r_inner, float r_outer, int ndiv, bool texture=0);
void draw_trunc_cone(point pos, vector3d v1, float length, float radius, float radius2, bool is_camera=0);
void draw_sphere_at(point const &pos, float radius, int ndiv);
void draw_sphere_at_tc(point const &pos, float radius, int ndiv, bool texture, bool cull);
void draw_subdiv_sphere(point const &pos, float radius, int ndiv, point const &vfrom, float const *perturb_map,
						int texture, bool disable_bfc, bool const *const render_map=NULL, float const *const exp_map=NULL,
						point const *const pt_shift=NULL, float expand=0.0, float s_beg=0.0, float s_end=1.0, float t_beg=0.0, float t_end=1.0);
void draw_subdiv_sphere(point const &pos, float radius, int ndiv, int texture, bool disable_bfc);
void draw_subdiv_sphere_section(point const &pos, float radius, int ndiv, int texture,
								float s_beg, float s_end, float t_beg, float t_end);
void rotate_sphere_tex_to_dir(vector3d const &dir);
void draw_cube_map_sphere(point const &pos, float radius, int ndiv, bool texture, bool disable_bfc=0);
void draw_torus(float ri, float ro, unsigned ndivi, unsigned ndivo, bool do_tex);
void rotate_towards_camera(point const &pos);
void draw_textured_square(float size, float z, int tid);
void draw_textured_square_alpha_test(float size, float z, int tid);
void draw_flare_no_blend(point const &pos, point const &xlate, float xsize, float ysize);
void draw_flare(point const &pos, point const &xlate, float xsize, float ysize);
void enable_flares(colorRGBA const &color, bool zoomed=0);
void disable_flares();
void draw_textured_quad(float xsize, float ysize, float z, int tid);
void draw_tquad(float xsize, float ysize, float z, bool texture);
void draw_one_tquad(float x1, float y1, float x2, float y2, float z, bool texture, float tx1=0.0, float ty1=0.0, float tx2=1.0, float ty2=1.0);
void draw_one_mult_tex_quad(float x1, float y1, float x2, float y2, float z, float tx1=0.0, float ty1=0.0, float tx2=1.0, float ty2=1.0);
void draw_billboard(point const &pos, point const &viewer, vector3d const &up_dir,
					float xsize, float ysize, float tx1=0.0, float ty1=0.0, float tx2=1.0, float ty2=1.0);
void draw_line_tquad(point const &p1, point const &p2, float w1, float w2, colorRGBA const &color1, colorRGBA const &color2, bool globalize);
void begin_line_tquad_draw();
void end_line_tquad_draw();
void draw_animated_billboard(point const &pos, float size, float timescale);
int  draw_simple_cube(cube_t const &c, bool texture, int in_cur_prim=PRIM_DISABLED, bool no_normals=0, int eflags=0,
	float texture_scale=1.0, vector3d const *const view_dir=NULL);
void draw_cube(point const &pos, float sx, float sy, float sz, bool texture, unsigned ndiv=1, bool scale_ndiv=0,
			   float texture_scale=1.0, bool proportional_texture=0, vector3d const *const view_dir=NULL);
void draw_z_plane(float x1, float y1, float x2, float y2, float zval, unsigned nx, unsigned ny);
int draw_cylin_quad_proj(cylinder_3dw const &cylin, vector3d const &view_dir, int in_cur_prim=PRIM_DISABLED, bool no_normals=0);
int  draw_simple_polygon(point const *const points, int npoints, vector3d const &norm, int in_cur_prim=PRIM_DISABLED, bool no_normals=0);
int  draw_simple_extruded_polygon(float thick, point const *const points, int npoints, int in_cur_prim=PRIM_DISABLED, bool no_normals=0);
void gen_quad_tex_coords(float *tdata, unsigned num, unsigned stride);
void gen_quad_tri_tex_coords(float *tdata, unsigned num, unsigned stride);
void free_dlists();
void setup_dlists();
void draw_cylin_fast(float r1, float r2, float l, int ndiv, bool texture, bool restore_matrix, bool r_approx=0);
void draw_sphere_dlist_raw(int ndiv, bool textured, bool half=0);
void draw_sphere_dlist(point const &pos, float radius, int ndiv, bool textured, bool half=0, bool bfc=0);
void draw_sphere_dlist_back_to_front(point const &pos, float radius, int ndiv, bool textured, bool half=0);
void draw_rotated_cylinder_dlist(point const &p1, point const &p2, float r, int ndiv, vector3d const &scale=zero_vector);

// function prototypes - draw mesh
float integrate_water_dist(point const &targ_pos, point const &src_pos, float const water_z);
void water_color_atten_pt(float *c, int x, int y, point const &pos, point const &p1, point const &p2);
float get_cloud_shadow_atten(int x, int y);
colorRGBA setup_mesh_lighting();
void run_post_mesh_draw();
void set_landscape_texgen(float tex_scale, int xoffset, int yoffset, int xsize, int ysize, bool use_detail_tex=1);
void display_mesh();
void draw_water_sides(int check_zvals);
float get_inf_terrain_fog_dist();

// function prototypes - tiled mesh
float draw_tiled_terrain(float wpz, bool reflection_pass);
void clear_tiled_terrain();
void reset_tiled_terrain_state();
void update_tiled_terrain_grass_vbos();
void draw_tiled_terrain_water(float zval);

// function prototypes - map_view
void draw_overhead_map();

// function prototypes - gen_obj
void gen_stars(float alpha, int half_sphere);
void gen_star(star &star1, int half_sphere);
void rand_xy_point(float zval, point &pt, unsigned flags);
void gen_object_pos(point &position, unsigned flags);
void gen_bubble(point const &pos, float r=0.0, colorRGBA const &c=WATER_C);
void gen_line_of_bubbles(point const &p1, point const &p2, float r=0.0, colorRGBA const &c=WATER_C);
bool gen_arb_smoke(point const &pos, colorRGBA const &bc, vector3d const &iv,
				   float r, float den, float dark, float dam, int src, int dt, bool as);
void gen_smoke(point const &pos);
bool gen_fire(point const &pos, float size, int source, bool allow_close=0, bool is_static=0, float light_bwidth=1.0, float intensity=1.0);
void gen_decal(point const &pos, float radius, vector3d const &orient, int cid=-1, float init_alpha=1.0, colorRGBA const &color=BLACK, bool is_glass_=0);
void gen_particles(point const &pos, unsigned num, float lt_scale=1.0, bool fade=0);
int gen_fragment(point const &pos, vector3d const &velocity, float size_mult, float time_mult,
	colorRGBA const &color, int tid, float tscale, int source, bool tri_fragment);
void gen_leaf_at(point const *const points, vector3d const &normal, int type, colorRGB const &color);
void gen_gauss_rand_arr();

// function prototypes - mesh_gen
bool bmp_to_chars(char *fname, char **&data);
bool verify_bmp_header(FILE *&fp, bool grayscale);
bool open_image_file(char *filename, FILE *&fp, bool is_bmp, bool is_grayscale);
void gen_mesh(int surface_type, int make_island, int keep_sin_table, int update_zvals);
float get_glaciated_zval(float zval);
float calc_glaciated_rel_value(float value);
float do_glaciate_exp(float value);
float get_rel_wpz();
void init_terrain_mesh();
float eval_mesh_sin_terms(float xv, float yv);
float eval_one_surface_point(float xval, float yval);
void reset_offsets();
float get_water_z_height();
void update_mesh(float dms, bool do_regen_trees);
bool is_under_mesh(point const &p);
bool read_mesh(const char *filename, float zmm=0.0);
bool write_mesh(const char *filename);
bool load_state(const char *filename);
bool save_state(const char *filename);

// function prototypes - physics
float get_max_t(int obj_type);
void init_objects();
void set_coll_rmax(float rmax);
void change_timestep(float mult_factor);
vector3d get_local_wind(point const &pt);
void reanimate_objects();
void accumulate_object(point const &pos, int type);
void shift_other_objs(vector3d const &vd);
void advance_physics_objects();
void reset_other_objects_status();
void auto_advance_time();

// function prototypes - ai
void advance_smiley(dwobject &obj, int smiley_id);
void shift_player_state(vector3d const &vd, int smiley_id);
void player_clip_to_scene(point &pos);
void smiley_action(int smiley_id);

// function prototypes - matrix
void set_scene_constants();
void alloc_matrices();
void delete_matrices();
void compute_matrices();
void update_matrix_element(int i, int j);
void update_mesh_height(int xpos, int ypos, int rad, float scale, float offset, int mode);
vector3d get_matrix_surf_norm(float **matrix, char **enabled, int xsize, int ysize, int i, int j);
void calc_matrix_normal_at(float **matrix, vector3d **vn, vector3d **sn, char **enabled, int xsize, int ysize, int i, int j);
void calc_matrix_normals(float **matrix, vector3d **vn, vector3d **sn, char **enabled, int xsize, int ysize);
void get_matrix_point(int xpos, int ypos, point &pt);
int  is_in_ice(int xpos, int ypos);
float interpolate_mesh_zval(float xval, float yval, float rad, int use_real_equation, int ignore_ice);
float int_mesh_zval_pt_off(point const &pos, int use_real_equation, int ignore_ice);
void calc_motion_direction();
float lowest_mesh_point(point const &pt, float radius);
float highest_mesh_point(point const &pt, float radius);

// function prototypes - collision detection
void reserve_coll_objects(unsigned size);
bool swap_and_set_as_coll_objects(coll_obj_group &new_cobjs);
int  add_coll_cube(cube_t &cube, cobj_params const &cparams, int platform_id=-1, int dhcm=0);
int  add_coll_cylinder(float x1, float y1, float z1, float x2, float y2, float z2,
					   float radius, float radius2, cobj_params const &cparams, int platform_id=-1, int dhcm=0);
int  add_coll_sphere(point const &pt, float radius, cobj_params const &cparams, int platform_id=-1, int dhcm=0);
int  add_coll_polygon(const point *points, int npoints, cobj_params const &cparams,
	float thickness, point const &xlate=all_zeros, int platform_id=-1, int dhcm=0);
int  remove_coll_object(int index, bool reset_draw=1);
int  remove_reset_coll_obj(int &index);
void purge_coll_freed(bool force);
void remove_all_coll_obj();
void cobj_stats();
int  collision_detect_large_sphere(point &pos, float radius, unsigned flags);
int  check_legal_move(int x_new, int y_new, float zval, float radius, int &cindex);
bool is_point_interior(point const &pos, float radius);

// function prototypes - objects
void free_cobj_draw_group_dlists();

// function prototypes - coll_cell_search
void build_cobj_tree(bool dynamic=0, bool verbose=1);
void add_to_cobj_tree(vector<unsigned> const &cobj_ixs, unsigned caller_id);
bool try_undo_last_add_to_cobj_tree(unsigned caller_id);
bool check_coll_line_exact_tree(point const &p1, point const &p2, point &cpos, vector3d &cnorm,
	int &cindex, int ignore_cobj, bool dynamic=0, int test_alpha=0, bool skip_non_drawn=0);
bool check_coll_line_tree(point const &p1, point const &p2, int &cindex, int ignore_cobj, bool dynamic=0, int test_alpha=0, bool skip_non_drawn=0);
bool cobj_contained_tree(point const &p1, point const &p2, point const &viewer, point const *const pts, unsigned npts,
	int ignore_cobj, int &cobj);
void get_coll_line_cobjs_tree(point const &pos1, point const &pos2, int ignore_cobj,
	vector<int> *cobjs, cobj_query_callback *cqc, bool dynamic, bool occlude);
void get_coll_sphere_cobjs_tree(point const &center, float radius, int cobj, vert_coll_detector &vcd, bool dynamic);
bool have_occluders();
void get_intersecting_cobjs_tree(cube_t const &cube, vector<unsigned> &cobjs, int ignore_cobj, float toler,
	bool dynamic, bool check_ccounter, int id_for_cobj_int);
bool check_coll_line(point pos1, point pos2, int &cindex, int c_obj, int skip_dynamic, int test_alpha);
bool check_coll_line_exact(point pos1, point pos2, point &cpos, vector3d &coll_norm, int &cindex, float splash_val=0.0,
						   int ignore_cobj=-1, bool fast=0, bool test_alpha=0, bool skip_dynamic=0);
bool cobj_contained(point pos1, point center, const point *pts, unsigned npts, int cobj);
bool is_pt_inside_or_near_cobj(point const &pt, float dist, int ignore_cobj, bool skip_dynamic);
bool is_occluded(vector<int> const &occluders, point const *const pts0, int npts, point const &camera);
void add_camera_cobj(point const &pos);
void force_onto_surface_mesh(point &pos);
int  set_true_obj_height(point &pos, point const &lpos, float step_height, float &zvel, int type, int id,
	bool flight, bool on_snow, bool skip_dynamic=0, bool test_only=0);

// function prototypes - math3d
float fix_angle(float angle);
vector3d get_poly_norm(point const *points);
void get_face_normal(shape3d &shape, int face_id);
void calc_reflection_angle(vector3d const &v_inc, vector3d &v_ref, vector3d const &norm);
bool calc_refraction_angle(vector3d const &v_inc, vector3d &v_ref, vector3d const &norm, float n1, float n2);
float get_fresnel_reflection(vector3d const &v_inc, vector3d const &norm, float n1, float n2);
float get_reflected_weight(float fresnel_ref, float alpha);
float get_coll_energy(vector3d const &v1, vector3d const &v2, float mass);
float triangle_area(point const *const points);
float polygon_area(point const *const points, unsigned npoints);
bool planar_contour_intersect(const point *points, unsigned npoints, point const &pos, vector3d const &norm);
bool point_in_polygon_2d(float xval, float yval, const point *points, int npts, int dx, int dy);
bool get_poly_zminmax(point const *const pts, unsigned npts, vector3d const &norm, float dval,
					  cube_t const &cube, float &z1, float &z2);
bool get_poly_zvals(vector<tquad_t> const &pts, float xv, float yv, float &z1, float &z2);
void gen_poly_planes(point const *const points, unsigned npoints, vector3d const &norm, float thick, point pts[2][4]);
void thick_poly_to_sides(point const *const points, unsigned npoints, vector3d const &norm, float thick, vector<tquad_t> &sides);
bool line_int_plane(point const &p1, point const &p2, point const &pp0, vector3d const &norm,
					point &p_int, float &t, bool ignore_t);
bool thick_poly_intersect(vector3d const &v1, point const &p1, vector3d const &norm,
						  point const pts[2][4], bool test_side, unsigned npoints);
bool sphere_intersect_poly_sides(vector<tquad_t> const &pts, point const &center, float radius, float &dist, vector3d &norm, bool strict);
bool pt_line_seg_dist_less_than(point const &P, point const &L1, point const &L2, float dist);
bool sphere_poly_intersect(const point *points, unsigned npoints, point const &pos, vector3d const &norm, float rdist, float radius);
bool sphere_ext_poly_int_base(point const &pt, vector3d const &norm, point const &pos, float radius,
							  float thickness, float &thick, float &rdist);
bool sphere_ext_poly_intersect(point const *const points, unsigned npoints, vector3d const &norm,
							   point const &pos, float radius, float thickness, float t_adj);
void get_sphere_mov_sphere_int_pt(point const &p1, point const &p2, vector3d const &v, float rsum, point &cpos);
bool sphere_test_comp(point const &p2, point const &p1, vector3d const &v1, float r2sq, float &t);
bool line_sphere_intersect(point const &p1, point const &p2, point const &c, float r);
bool circle_test_comp(point const &p2, point const &p1, vector3d const &v1, vector3d norm, float r2sq, float &t);
void dir_to_sphere_s_t(vector3d const &dir, vector3d const &sdir, double &s, double &t);
bool line_sphere_intersect_s_t(point const &p1, point const &p2, point const &sc, float radius,
							   vector3d const &sdir, double &s, double &t);
bool line_sphere_int(vector3d const &v1, point const &p1, point const &center, float radius, point &lsint, bool test_neg_t);
bool line_intersect_sphere(point const &p1, vector3d const &v12, point const &sc, float radius, float &rad, float &dist, float &t);
void get_sphere_border_pts(point *qp, point const &pos, point const &viewed_from, float radius, unsigned num_pts);
bool line_torus_intersect(point const &p1, point const &p2, point const &tc, float ri, float ro, float &t);
bool sphere_torus_intersect(point const &sc, float sr, point const &tc, float ri, float ro, point &p_int, vector3d &norm, bool calc_int);
bool circle_rect_intersect(point const &pos, float radius, cube_t const &cube);
bool sphere_cube_intersect(point const &pos, float radius, cube_t const &cube);
bool sphere_cube_intersect(point const &pos, float radius, cube_t const &cube, point const &p_last,
						   point &p_int, vector3d &norm, unsigned &cdir, bool check_int, bool skip_z=0);
bool do_line_clip(point &v1, point &v2, float const d[3][2]);
bool get_line_clip(point const &v1, point const &v2, float const d[3][2], float &tmin, float &tmax);
bool get_line_clip2(point const &v1, vector3d const &dinv, float const d[3][2]);
bool check_line_clip_expand(point const &v1, point const &v2, float const d[3][2], float expand);
float line_line_dist(point const &p1a, point const &p1b, point const &p2a, point const &p2b);
float get_cylinder_params(point const &cp1, point const &cp2, point const &pos, vector3d &v1, vector3d &v2);
int  line_intersect_trunc_cone(point const &p1, point const &p2, point const &cp1, point const &cp2,
							   float r1, float r2, bool check_ends, float &t);
bool line_intersect_cylinder(point const &p1, point const &p2, cylinder_3dw const &c, bool check_ends);
int  line_int_thick_cylinder(point const &p1, point const &p2, point const &cp1, point const &cp2,
							 float ri1, float ri2, float ro1, float ro2, bool check_ends, float &t);
bool sphere_int_cylinder_pretest(point const &sc, float sr, point const &cp1, point const &cp2, float r1, float r2,
								 bool check_ends, vector3d &v1, vector3d &v2, float &t, float &rad);
bool sphere_intersect_cylinder_ipt(point const &sc, float sr, point const &cp1, point const &cp2, float r1, float r2,
							   bool check_ends, point &p_int, vector3d &norm, bool calc_int);
void cylinder_quad_projection(point *pts, cylinder_3dw const &c, vector3d const &v1, vector3d &v2, int &npts);
template<typename T> pointT<T> get_center_arb(pointT<T> const *const pts, int npts);
unsigned get_cube_corners(float const d[3][2], point corners[8], point const &viewed_from=all_zeros, bool all_corners=1);
void get_closest_cube_norm(float const d[3][2], point const &p, vector3d &norm);
void cylinder_bounding_sphere(point const *const pts, float r1, float r2, point &center, float &radius);
void polygon_bounding_sphere(const point *pts, int npts, float thick, point &center, float &radius);
void add_rotated_quad_pts(vert_norm *points, unsigned &ix, float theta, float rd, float z, point const &pos, vector3d const &scale);
void vproj_plane(vector3d const &vin, vector3d const &n, vector3d &vout);
template<typename T> void rotate_vector3d(pointT<T> vin, pointT<T> const &vrot, double angle, pointT<T> &vout);
template<typename T> void rotate_vector3d_multi(pointT<T> const &vrot, double angle, pointT<T> *vout, unsigned nv);
void rotate_vector3d_x2(point const &vrot, double angle, point &vout1, point &vout2);
float angle_of_projected_vectors(vector3d const &v1, vector3d const &v2, vector3d n);
vector3d rtp_to_xyz(float radius, double theta, double phi);
vector3d gen_rand_vector_uniform(float mag);
vector3d gen_rand_vector(float mag, float zscale=1.0, float phi_term=PI);
vector3d gen_rand_vector2(float mag, float zscale=1.0, float phi_term=PI);
vector3d lead_target(point const &ps, point const &pt, vector3d const &vs, vector3d const &vt, float vweap);
vector3d get_firing_dir(vector3d const &src, vector3d const &dest, float fvel, float gravity_scale);

// function prototypes - water
bool get_water_enabled(int x, int y);
bool has_water(int x, int y);
bool mesh_is_underwater(int x, int y);
void water_color_atten_at_pos(colorRGBA &c, point const &pos);
void select_water_ice_texture(colorRGBA &color, float *use_this_temp=NULL);
void draw_water();
void add_splash(int xpos, int ypos, float energy, float radius, bool add_sound);
bool add_water_section(float x1, float y1, float x2, float y2, float zval, float wvol);
void float_downstream(point &pos, float radius);
void calc_watershed();
bool is_underwater(point const &pos, int check_bottom=0, float *depth=NULL);
void select_liquid_color(colorRGBA &color, int xpos, int ypos);
void select_liquid_color(colorRGBA &color, point const &pos);
float get_blood_mix(point const &pos);
void add_water_spring(point const &pos, vector3d const &vel, float rate, float diff, int calc_z, int gen_vel);
void shift_water_springs(vector3d const &vd);
void update_water_zvals(int x1, int y1, int x2, int y2);

// function prototypes - lightning
void compute_volume_matrix();

// function prototypes - textures
void load_texture_names();
void load_textures();
int get_texture_by_name(std::string const &name);
bool select_texture(int id, bool enable=1, bool white_tex_default=0);
float get_tex_ar(int id);
void bind_1d_texture(unsigned tid);
void bind_2d_texture(unsigned tid);
void setup_texture(unsigned &tid, int type, bool mipmap, bool wrap_s, bool wrap_t,
	bool mirror_s=0, bool mirror_t=0, bool nearest=0, float anisotropy=1.0);
void free_textures();
void reset_textures();
void free_texture(unsigned &tid);
void setup_landscape_tex_colors(colorRGBA const &c1, colorRGBA const &c2);
colorRGBA texture_color(int tid);
unsigned get_texture_size(int tid, bool dim);
void get_lum_alpha(colorRGBA const &color, int tid, float &luminance, float &alpha);
std::string get_file_extension(std::string const &filename, unsigned level, bool make_lower);
colorRGBA get_landscape_texture_color(int xpos, int ypos);
void update_lttex_ix(int &ix);
void get_tids(float relh, int NTEXm1, float const *const h_tex, int &k1, int &k2, float &t);
void create_landscape_texture();
float add_crater_to_landscape_texture(float xval, float yval, float radius);
void add_color_to_landscape_texture(colorRGBA const &color, float xval, float yval, float radius, int check_unique);
void add_snow_to_landscape_texture(point const &pos, float acc);
void update_landscape_texture();
void gen_tex_height_tables();
void set_texgen_vec4(float const v[4], bool s_or_t, bool enable_and_set_mode, shader_t *shader=NULL);
void setup_texgen_full(float sx, float sy, float sz, float sw, float tx, float ty, float tz, float tw, int mode=GL_EYE_LINEAR, shader_t *shader=NULL);
void setup_texgen(float xscale, float yscale, float tx, float ty, float z_off=0.0, int mode=GL_EYE_LINEAR);
void disable_texgen();
void disable_textures_texgen();
void setup_polygon_texgen(vector3d const &norm, float const scale[2], float const xlate[2], vector3d const &offset, bool swap_txy=0, shader_t *shader=NULL);
void get_tex_coord(vector3d const &dir, vector3d const &sdir, unsigned txsize, unsigned tysize, int &tx, int &ty, bool invert);
float get_texture_component(unsigned tid, float xval, float yval, int comp);
bool is_billboard_texture_transparent(point const *const points, point const &pos, int tid);
void set_texture_specular(bool val);

// function prototypes - sun flares
void DoFlares(point const &from, point const &at, point const &light, float near_clip, float size, float intensity);
void load_flare_textures();
void free_flare_textures();

// function prototypes - ocean
void draw_ocean();
double gamma (double x);
double MitsuyasuDistribution (double f, double theta);
double EPM(double f);
double EnergyDistribution(double f, double theta);
double Amplitude(double f, double theta, double k);
void AnimateWater();
void InitWater();
void calc_ocean_normals();

// function prototypes - gameplay/ai
bool camera_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool smiley_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool landmine_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool health_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool shield_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool powerup_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool weapon_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool ammo_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool pack_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool rock_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool sball_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool dodgeball_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);
bool skull_collision(int index, int obj_index, vector3d const &velocity, point const &position, float energy, int type);

void gen_rocket_smoke(point const &pos, vector3d const &orient, float radius);
int get_smiley_hit(vector3d &hdir, int index);
void blast_radius(point const &pos, int type, int obj_index, int shooter, int chain_level);
void create_explosion(point const &pos, int shooter, int chain_level, float damage, float size, int type, bool cview);
void do_area_effect_damage(point &pos, float effect_radius, float damage, int index, int source, int type);
void switch_player_weapon(int val);
void draw_beams();
void show_blood_on_camera();
void update_weapon_cobjs();
int select_dodgeball_texture(int shooter);
void draw_weapon_simple(point const &pos, vector3d const &dir, float radius, int cid, int wid, float scale);
void draw_weapon_in_hand(int shooter);
bool weap_has_transparent(int shooter);
void draw_scheduled_weapons();
void add_weapon_lights(int shooter);
void show_crosshair(int do_zoom);
void show_user_stats();
void show_other_messages();
void print_text_onscreen(std::string const &text, colorRGBA const &color, float size, int time, int priority=0, bool bitmap=0);
void print_weapon(int weapon_id);
bool check_underwater(int who, float &depth);
void player_fall(int id);
void update_camera_velocity(vector3d const &v);
void init_game_state();
void gamemode_rand_appear();
bool has_invisibility(int id);
void init_smileys();
void init_game_mode();
void update_game_frame();
void change_game_mode();
void free_dodgeballs(bool camera, bool smileys);
int gen_smiley_or_player_pos(point &pos, int index);
colorRGBA get_smiley_team_color(int smiley_id);
void select_smiley_texture(int smiley_id);
void free_smiley_textures();
int get_ammo_or_obj(int wid);
int wid_need_weapon(int wid);

// function prototypes - explosion
void update_blasts();
void draw_blasts();

// function prototypes - scenery
void gen_scenery();
void draw_scenery(bool draw_opaque, bool draw_transparent, bool shadow_only=0);
void update_scenery_zvals(int x1, int y1, int x2, int y2);
void free_scenery();
void do_rock_damage(point const &pos, float radius, float damage);
void add_scenery_cobjs();
void shift_scenery(vector3d const &vd);
void add_plant(point const &pos, float height, float radius, int type, int calc_z);

// function prototypes - grass
void setup_wind_for_shader(shader_t &s, unsigned tu_id);
bool no_grass();
void gen_grass(bool full_regen);
void update_grass_vbos();
void draw_grass();
void modify_grass_at(point const &pos, float radius, bool crush=0, bool burn=0, bool cut=0, bool update_mh=0, bool check_uw=0);
bool place_obj_on_grass(point &pos, float radius);
float get_grass_density(point const &pos);

// function prototypes - draw mech
void draw_hmv();
void build_hmv_shape();
void delete_hmv_shape();
void add_shape_coll_objs();
void shift_hmv(vector3d const &vd);

// function prototypes - tree + sm_tree (see also tree_3dw.h)
colorRGBA get_tree_trunk_color(int type, bool modulate_with_texture);
int get_tree_class_from_height(float zpos);
int get_tree_type_from_height(float zpos);
void set_leaf_shader(shader_t &s, float min_alpha, bool gen_tex_coords=0, bool use_geom_shader=0, unsigned tc_start_ix=0);

// function prototypes - csg
void get_cube_points(const float d[3][2], point pts[8]);

// function prototypes - ship
upos_point_type const &get_player_pos();
vector3d const &get_player_dir();
vector3d const &get_player_up();
void set_player_pos(point const &pos_);
void set_player_dir(vector3d const &dir_);
void set_player_up(vector3d const &upv_);
void init_universe_display();
void set_univ_pdu();
void setup_current_system();
void apply_univ_physics();
void draw_universe(bool static_only=0, bool skip_closest=0, bool no_distant=0);
void draw_universe_stats();
void free_ship_dlists();
void clear_univ_obj_contexts();

// function prototypes - lightmap
void update_flow_for_voxels(cube_t const &cube);
void shift_light_sources(vector3d const &vd);
void shift_lightmap(vector3d const &vd);
void regen_lightmap();
void clear_lightmap();
void build_lightmap(bool verbose);
void add_smoke(point const &pos, float val);
void distribute_smoke();
float get_smoke_at_pos(point const &pos);
void add_line_light(point const &p1, point const &p2, colorRGBA const &color, float size, float intensity=1.0);
void add_dynamic_light(float sz, point const &p, colorRGBA const &c=WHITE, vector3d const &d=plus_z, float bw=1.0);
colorRGBA gen_fire_color(float &cval, float &inten, float rate=1.0);
void clear_dynamic_lights();
void add_camera_flashlight();
void add_camera_candlelight();
void add_dynamic_lights();
void get_xyz(point const &p, int v[3]);
void get_xyz_v2(point &p, int const v[3]);
void update_smoke_indir_tex_range(unsigned x_start, unsigned x_end, unsigned y_start, unsigned y_end, bool update_lighting);
bool upload_smoke_indir_texture();
void upload_dlights_textures();
void setup_dlight_textures(shader_t &s);
bool is_shadowed_lightmap(point const &p);
bool is_in_darkness(point const &pos, float radius, int cobj);
bool get_dynamic_light(int x, int y, int z, point const &p, float lightscale, float *ls, vector3d const *const norm, float const *const spec);
void get_sd_light(int x, int y, int z, point const &p, bool no_dynamic, float lightscale, float *ls, vector3d const *const norm, float const *const spec);
float get_indir_light(colorRGBA &a, point const &p, bool no_dynamic, bool shadowed, vector3d const *const norm, float const *const spec);
unsigned enable_dynamic_lights(point const center=all_zeros, float radius=0.0);
void disable_dynamic_lights(unsigned num_dlights);

// function prototypes - tessellate
void split_polygon_to_cobjs(coll_obj const &cobj, coll_obj_group &split_polygons, vector<point> const &poly_pt, bool split_quads);

// function prototypes - shaders
char const *append_array_ix(std::string &s, unsigned i);
bool setup_shaders();
void clear_shaders();

// function prototypes - snow
bool snow_enabled();
void gen_snow_coverage();
void reset_snow_vbos();
void draw_snow();
bool get_snow_height(point const &p, float radius, float &zval, vector3d &norm, bool crush_snow);

// function prototypes - waypoints
void create_waypoints(vector<user_waypt_t> const &user_waypoints);
void shift_waypoints(vector3d const &vd);
void draw_waypoints();

// function prototypes - destroy_cobj
void destroy_coll_objs(point const &pos, float damage, int shooter, bool big, float force_radius=0.0);
void check_falling_cobjs();

// function prototypes - shadow_map
bool shadow_map_enabled();
unsigned get_shadow_map_tu_id(int light);
unsigned get_shadow_map_tid(int light);
int get_smap_ndiv(float radius);
bool set_smap_shader_for_light(shader_t &s, int light, float z_bias);
void set_smap_shader_for_all_lights(shader_t &s, float z_bias=DEF_Z_BIAS);
pos_dir_up get_pt_cube_frustum_pdu(point const &pos, cube_t const &bounds, bool set_matrix);
void draw_scene_bounds_and_light_frustum(point const &lpos);
void create_shadow_map();
void free_shadow_map_textures();

// function prototypes - raytrace
float get_scene_radius();
void check_update_global_lighting(unsigned lights);

// function prototypes - voxels
void gen_voxel_landscape();
bool gen_voxels_from_cobjs(coll_obj_group &cobjs);
void gen_voxel_asteroid(voxel_model_space &model, point const &center, float radius, unsigned size, int rseed=456);
bool parse_voxel_option(FILE *fp);
void render_voxel_data(bool shadow_pass);
void free_voxel_context();
bool point_inside_voxel_terrain(point const &pos);
float get_voxel_terrain_ao_lighting_val(point const &pos);
bool update_voxel_sphere_region(point const &center, float radius, float val_at_center, int shooter, unsigned num_fragments=0);
void proc_voxel_updates();

// function prototypes - screenshot (these are C functions)
#ifdef ENABLE_JPEG
int screenshot(unsigned window_width, unsigned window_height, char *file_path);
int write_jpeg(unsigned window_width, unsigned window_height, char *file_path);
#else // why compile as C when libjpeg isn't needed?
int screenshot(unsigned window_width, unsigned window_height, char *file_path);
int write_jpeg(unsigned window_width, unsigned window_height, char *file_path);
#endif


#include "inlines.h"


#endif // _FUNCTION_REGISTRY_H_

