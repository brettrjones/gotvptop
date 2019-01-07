// Derivative of Android Chat Widget https://github.com/ijarobot/ ( Apache License )
package com.p2pgotv.gotvstation;

import java.util.ArrayList;
import java.util.List;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v4.view.ViewPager.OnPageChangeListener;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.FrameLayout.LayoutParams;
import android.widget.GridView;
import android.widget.ImageView;
import android.widget.LinearLayout;

@SuppressLint("InflateParams")
public class ChatFacePageFragment extends Fragment 
{

	public static final String ARG_POSITION 	= "position";
	public static final String ARG_FACE_DATA 	= "ARG_FACE_DATA";

	private ChatOnOperationListener 	m_OnOperationListener;
	private List<String> 				m_FragmentList;
	private ViewPager 					m_FaceViewPager;
	private LinearLayout 				m_PagePointLayout;
	private int 						m_ArgPosition;

	Activity 							m_ParentActivity;
	List<View> 							m_FaceGridViewList;
	List<ImageView> 					m_PointViews;

	//========================================================================
	@Override
	public void onCreate(Bundle savedInstanceState) 
	{
		super.onCreate(savedInstanceState);
		m_ParentActivity 	= (Activity) getActivity();
		m_ArgPosition 		= getArguments().getInt(ARG_POSITION);
		m_FragmentList 	 	= getArguments().getStringArrayList(ARG_FACE_DATA);
	}
	
	//========================================================================
	@Override
	public View onCreateView(	LayoutInflater inflater,
								@Nullable ViewGroup container, 
								@Nullable Bundle savedInstanceState ) 
	{
		m_FaceGridViewList 	= new ArrayList<View>();
		m_PointViews 		= new ArrayList<ImageView>();
		View rootView 		= inflater.inflate( R.layout.chat_face_fragment, null );
		m_FaceViewPager 	= (ViewPager) rootView.findViewById( R.id.faceViewPager );
		m_PagePointLayout 	= (LinearLayout) rootView.findViewById( R.id.pagePointLayout );

		for( int x = 0; x < (m_FragmentList.size() % 12 == 0 ? m_FragmentList.size() / 12 : (m_FragmentList.size() / 12) + 1); x++ ) 
		{
			GridView view = new GridView( m_ParentActivity );
			ChatFaceAdapter faceAdapter = new ChatFaceAdapter( m_ParentActivity, 
					m_FragmentList.subList(x * 12, ((x + 1) * 12) > m_FragmentList.size() ? m_FragmentList.size() : ((x + 1) * 12)));
			view.setAdapter(faceAdapter);
			view.setOnItemClickListener(new OnItemClickListener() 
			{
				@Override
				public void onItemClick( AdapterView<?> parent, View view, int position, long id ) 
				{
					if( null != m_OnOperationListener ) 
					{
						m_OnOperationListener.chatSelectedFace( m_FragmentList.get(position) );
					}
				}
			});
			
			view.setNumColumns(4);

			view.setBackgroundColor(Color.TRANSPARENT);
			view.setHorizontalSpacing(1);
			view.setVerticalSpacing(1);
			view.setStretchMode(GridView.STRETCH_COLUMN_WIDTH);
			view.setCacheColorHint(0);
			view.setPadding(5, 0, 5, 0);
			view.setSelector(new ColorDrawable(Color.TRANSPARENT));
			view.setLayoutParams(new LayoutParams( LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT ));
			view.setGravity(Gravity.CENTER);

			m_FaceGridViewList.add(view);

			ImageView imageView = new ImageView( m_ParentActivity );
			imageView.setBackgroundResource( R.drawable.point_normal );
			LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(
					new ViewGroup.LayoutParams( LayoutParams.WRAP_CONTENT,
					LayoutParams.WRAP_CONTENT ));
			layoutParams.leftMargin = 10;
			layoutParams.rightMargin = 10;
			layoutParams.width = 8;
			layoutParams.height = 8;
			m_PagePointLayout.addView( imageView, layoutParams );
			if( x == 0 ) 
			{
				imageView.setBackgroundResource( R.drawable.point_selected );
			}
			
			m_PointViews.add( imageView );
		}

		PagerAdapter facePagerAdapter = new FacePagerAdapter( m_FaceGridViewList );
		m_FaceViewPager.setAdapter( facePagerAdapter );
		m_FaceViewPager.setOnPageChangeListener( new OnPageChangeListener() 
		{
			@Override
			public void onPageSelected(int index) 
			{
				for (int i = 0; i < m_PointViews.size(); i++) 
				{
					if (index == i) 
					{
						m_PointViews.get(i).setBackgroundResource(R.drawable.point_selected);
					} 
					else 
					{
						m_PointViews.get(i).setBackgroundResource(R.drawable.point_normal);
					}
				}		
			}

			@Override
			public void onPageScrolled(int arg0, float arg1, int arg2) 
			{
			}

			@Override
			public void onPageScrollStateChanged(int arg0) 
			{
			}
		});

		return rootView;
	}

	//========================================================================
	public class FacePagerAdapter extends PagerAdapter 
	{	
		private List<View> gridViewList;
		public FacePagerAdapter(List<View> gridViewList) 
		{
			this.gridViewList = gridViewList;
		}

		@Override
		public int getCount() 
		{
			return gridViewList.size();
		}

		@Override
		public boolean isViewFromObject(View arg0, Object arg1) 
		{
			return arg0 == arg1;
		}

		@Override
		public int getItemPosition(Object object) 
		{
			return super.getItemPosition(object);
		}

		@Override
		public void destroyItem(View arg0, int arg1, Object arg2) 
		{
			((ViewPager) arg0).removeView(gridViewList.get(arg1));
		}

		@Override
		public Object instantiateItem(View arg0, int arg1) 
		{
			((ViewPager) arg0).addView(gridViewList.get(arg1));
			return gridViewList.get(arg1);
		}
	}

	//========================================================================
	public ChatOnOperationListener getOnOperationListener() 
	{
		return m_OnOperationListener;
	}

	//========================================================================
	public void setOnOperationListener( ChatOnOperationListener onOperationListener ) 
	{
		this.m_OnOperationListener = onOperationListener;
	}
}
