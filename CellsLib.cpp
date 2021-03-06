#include "CellsLib.h"
#include "CellsModel.h"
#include <QHeaderView>
#include <QBoxLayout>


namespace Netlist {
	CellsLib::CellsLib ( QWidget* parent )
		: QWidget         (parent)
		, cellViewer_    (NULL)
		, baseModel_     (new  CellsModel(this))
		, view_           (new  QTableView(this))
		, load_           (new  QPushButton(this))
		{
			setAttribute( Qt:: WA_QuitOnClose   , false  );
			setAttribute( Qt:: WA_DeleteOnClose , false );
			setContextMenuPolicy( Qt:: ActionsContextMenu  );
			view_ ->setShowGrid               ( false  );
			view_ ->setAlternatingRowColors( true );
			view_ ->setSelectionBehavior    ( QAbstractItemView :: SelectRows  );
			view_ ->setSelectionMode         ( QAbstractItemView :: SingleSelection  );
			view_ ->setSortingEnabled       ( true );
			view_ ->setModel                  ( baseModel_  );

			setWindowTitle(tr("Open Cell"));

			QHeaderView* horizontalHeader = view_ ->horizontalHeader ();
			horizontalHeader ->setDefaultAlignment   ( Qt:: AlignHCenter  );
			horizontalHeader ->setMinimumSectionSize( 300 );
			horizontalHeader ->setStretchLastSection( true );
			QHeaderView* verticalHeader = view_ ->verticalHeader ();
			verticalHeader ->setVisible(true );

			QHBoxLayout* hLayout = new  QHBoxLayout();
			hLayout ->addStretch ();
			hLayout ->addWidget (load_);
			hLayout ->addStretch ();
			QFrame* separator = new  QFrame();
			separator ->setFrameShape(QFrame::HLine);
			separator ->setFrameShadow(QFrame::Sunken);
			QVBoxLayout* vLayout = new  QVBoxLayout();
			vLayout ->setSizeConstraint(QLayout::SetFixedSize);
			vLayout ->addWidget(view_);
			vLayout ->addLayout(hLayout);
			setLayout(vLayout);

			load_ ->setText( "Load" );
			connect( load_ , SIGNAL(clicked ()), this , SLOT(load()) );
		}

		CellsLib::~CellsLib() {
			delete baseModel_;
			delete view_;
			delete load_;
		}

		int   CellsLib::getSelectedRow  ()  const
		{
			QModelIndexList  selecteds = view_ ->selectionModel ()
			->selection (). indexes ();
			if (selecteds.empty ())  return  -1;
			return  selecteds.first ().row ();
		}

		void   CellsLib::load ()
		{
			int  selectedRow = getSelectedRow ();
			if (selectedRow  < 0)  return;
			cellViewer_ ->setCell( baseModel_ ->getModel(selectedRow) );
		}
}
